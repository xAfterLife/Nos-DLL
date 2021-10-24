#include "hooking.h"

constexpr auto HOOK_SIZE = 6;
constexpr auto TRAMPOLINE_SIZE = HOOK_SIZE + 14;

constexpr auto ASM_OP_PUSHAD = 0x60;
constexpr auto ASM_OP_PUSHFD = 0x9C;
constexpr auto ASM_OP_POPAD = 0x61;
constexpr auto ASM_OP_POPFD = 0x9D;
constexpr auto ASM_OP_CALL = 0xE8;
constexpr auto ASM_OP_JMP = 0xE9;
constexpr auto ASM_OP_NOP = 0x90;
constexpr auto ASM_OP_RET = 0xC3;

LPVOID Hooking::CreateTrampoline (LPVOID lpfnTarget, LPVOID lpfnHook, const LPBYTE lpBytesBackup)
{
	DWORD fdw_dummy;

	// Allocate the memory for the trampoline function
	auto* lp_trampoline = VirtualAlloc(nullptr, TRAMPOLINE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!lp_trampoline)
		return nullptr;

	// Compute the addresses beforehand (just for clarity)
	const auto PDW_PUSH_REGS_ADDY = reinterpret_cast<DWORD_PTR>(lp_trampoline);
	const auto PDW_HOOK_CALL_ADDY = PDW_PUSH_REGS_ADDY + 2;
	const auto PDW_POP_REGS_ADDY = PDW_HOOK_CALL_ADDY + 5;
	const auto PDW_BYTES_BACKUP_ADDY = PDW_POP_REGS_ADDY + 2;
	const auto PDW_BACKJUMP_ADDY = PDW_BYTES_BACKUP_ADDY + HOOK_SIZE;

	// Write the trampoline to memory
	// 
	// PUSHAD                             ; backup the registers
	// PUSHFD                             ; backup the flags
	// CALL lpfnHook                      ; call the hook function
	// POPFD                              ; restore the flags
	// POPAD                              ; restore the registers
	// ...                                ; execute backed up instructions
	// JMP lpfnTarget + HOOK_SIZE         ; jump back to the target function

	*reinterpret_cast<BYTE*>(PDW_PUSH_REGS_ADDY) = ASM_OP_PUSHAD;
	*reinterpret_cast<BYTE*>(PDW_PUSH_REGS_ADDY + 1) = ASM_OP_PUSHFD;

	*reinterpret_cast<BYTE*>(PDW_HOOK_CALL_ADDY) = ASM_OP_CALL;
	*reinterpret_cast<DWORD*>(PDW_HOOK_CALL_ADDY + 1) = reinterpret_cast<DWORD_PTR>(lpfnHook) - PDW_HOOK_CALL_ADDY - 5;

	*reinterpret_cast<BYTE*>(PDW_POP_REGS_ADDY) = ASM_OP_POPFD;
	*reinterpret_cast<BYTE*>(PDW_POP_REGS_ADDY + 1) = ASM_OP_POPAD;

	if (!memcpy(reinterpret_cast<LPVOID>(PDW_BYTES_BACKUP_ADDY), lpBytesBackup, HOOK_SIZE))
	{
		VirtualFree(lp_trampoline, 0, MEM_RELEASE);
		return nullptr;
	}

	*reinterpret_cast<BYTE*>(PDW_BACKJUMP_ADDY) = ASM_OP_JMP;
	*reinterpret_cast<DWORD*>(PDW_BACKJUMP_ADDY + 1) = reinterpret_cast<DWORD_PTR>(lpfnTarget) + HOOK_SIZE - PDW_BACKJUMP_ADDY - 5;

	// Change the access protection to make the trampoline function executable
	if (!VirtualProtect(lp_trampoline, TRAMPOLINE_SIZE, PAGE_EXECUTE_READ, &fdw_dummy) || !FlushInstructionCache(GetCurrentProcess(), lp_trampoline, TRAMPOLINE_SIZE))
	{
		VirtualFree(lp_trampoline, 0, MEM_RELEASE);
		return nullptr;
	}

	return lp_trampoline;
}

BOOL Hooking::HookFunction (LPVOID lpfnTarget, const LPVOID lpfnHook)
{
	DWORD fdw_old_protect;
	BYTE a_bytes_backup[HOOK_SIZE];

	// Change access protection of the target function's bytes where the jump will be written
	if (!VirtualProtect(lpfnTarget, HOOK_SIZE, PAGE_EXECUTE_READWRITE, &fdw_old_protect))
	{
		return FALSE;
	}

	// Backup the instructions that will be overwritten
	if (!memcpy(a_bytes_backup, lpfnTarget, HOOK_SIZE))
		return FALSE;

	// Create a trampoline that will call the hook function, execute the overwritten instructions, and jump back
	auto* lp_trampoline = CreateTrampoline(lpfnTarget, lpfnHook, a_bytes_backup);
	if (!lp_trampoline)
		return FALSE;

	// Write a jump to the trampoline function
	*static_cast<BYTE*>(lpfnTarget) = ASM_OP_JMP;
	*reinterpret_cast<DWORD*>(reinterpret_cast<DWORD_PTR>(lpfnTarget) + 1) = reinterpret_cast<DWORD_PTR>(lp_trampoline) - reinterpret_cast<DWORD_PTR>(lpfnTarget) - 5;
	*reinterpret_cast<BYTE*>(reinterpret_cast<DWORD_PTR>(lpfnTarget) + 5) = ASM_OP_NOP;

	// Restore the old access protection of the target function's bytes
	VirtualProtect(lpfnTarget, HOOK_SIZE, fdw_old_protect, &fdw_old_protect);

	return TRUE;
}

BOOL Hooking::UnhookFunction (LPVOID lpfnTarget)
{
	DWORD fdw_old_protect;
	DWORD_PTR p_offset;

	// Retrieve trampoline and bytesBackup addresses
	if (!memcpy(&p_offset, reinterpret_cast<LPVOID>(reinterpret_cast<DWORD_PTR>(lpfnTarget) + 1), 5))
		return FALSE;
	auto* const LP_TRAMPOLINE = reinterpret_cast<LPVOID>(reinterpret_cast<DWORD_PTR>(lpfnTarget) + p_offset + 5);
	const auto* lp_bytes_backup = static_cast<LPBYTE>(LP_TRAMPOLINE) + 9;

	// Change access protection of the target function's bytes where the backup will be restored
	if (!VirtualProtect(lpfnTarget, HOOK_SIZE, PAGE_EXECUTE_READWRITE, &fdw_old_protect))
		return FALSE;

	// Restore the backup of the instructions previously overwritten
	if (!memcpy(lpfnTarget, lp_bytes_backup, HOOK_SIZE))
		return FALSE;

	// Restore the old access protection of the target function's bytes
	if (!VirtualProtect(lpfnTarget, HOOK_SIZE, fdw_old_protect, &fdw_old_protect))
		return FALSE;

	// Free the memory previously allocated for the trampoline
	return VirtualFree(LP_TRAMPOLINE, 0, MEM_RELEASE);
}
