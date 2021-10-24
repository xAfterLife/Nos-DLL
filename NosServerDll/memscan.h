#pragma once
#include <windows.h>

#define IMAGE_BASE 0x00400000   // Default location; NosTale doesn't use ASLR
#define IMAGE_SIZE 0x004B4FFF

#define Memscan AC11D6617A8A450080F6B3B88C5E4E84
#define FindPattern DCAC94ABD2CC459C98BC56813844321F
#define PatternScan EBDA6D9D3C434ABDBA6CFD0528C14726

class Memscan
{
public:
	static LPVOID FindPattern (const BYTE* lpPattern, LPCSTR szMask);
	static uintptr_t PatternScan (void* module, const char* signature);
};
