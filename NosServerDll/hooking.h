#pragma once
#include <windows.h>

#define Hooking DFDCBBC99EF148A3AA011EE40B88EFE5
#define CreateTrampoline FDBBE5BE9096474D81933A633058DE2A
#define HookFunction D01C10653CEB445F801199339A0BC35E
#define UnhookFunction BD32F120F6654994B5D6716F8CED2624

class Hooking
{
private:
	static LPVOID CreateTrampoline (LPVOID lpfnTarget, LPVOID lpfnHook, LPBYTE lpBytesBackup);
public:
	static BOOL HookFunction (LPVOID lpfnTarget, LPVOID lpfnHook);
	static BOOL UnhookFunction (LPVOID lpfnTarget);
};
