#include "memscan.h"

#include <vector>

LPVOID Memscan::FindPattern (const BYTE* lpPattern, const LPCSTR szMask)
{
	const DWORD DW_LENGTH = strlen(szMask);
	const auto DW_IMAGE_END = IMAGE_BASE + IMAGE_SIZE - DW_LENGTH;
	DWORD_PTR i;

	// Scan the whole image for the pattern
	for (DWORD_PTR j = IMAGE_BASE; j < DW_IMAGE_END; ++j)
	{
		// If the pattern is found, return the address at which it begins
		for (i = 0; i < DW_LENGTH && (szMask[i] == '?' || *reinterpret_cast<BYTE*>(j + i) == lpPattern[i]); ++i);
		if (i == DW_LENGTH)
			return reinterpret_cast<LPVOID>(j);
	}

	return nullptr;
}

uintptr_t Memscan::PatternScan (void* module, const char* signature)
{
	static auto pattern_to_byte = [](const char* pattern)
	{
		auto bytes = std::vector<int>{};
		auto* const START = const_cast<char*>(pattern);
		auto* const END = const_cast<char*>(pattern) + strlen(pattern);

		for (auto* current = START; current < END; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else
			{
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto* const DOS_HEADER = static_cast<PIMAGE_DOS_HEADER>(module);
	auto* const NT_HEADERS = (PIMAGE_NT_HEADERS)(static_cast<std::uint8_t*>(module) + DOS_HEADER->e_lfanew);

	const auto SIZE_OF_IMAGE = NT_HEADERS->OptionalHeader.SizeOfImage;
	auto pattern_bytes = pattern_to_byte(signature);
	auto* const SCAN_BYTES = static_cast<std::uint8_t*>(module);

	const auto S = pattern_bytes.size();
	auto* const D = pattern_bytes.data();

	for (auto i = 0ul; i < SIZE_OF_IMAGE - S; ++i)
	{
		auto found = true;
		for (auto j = 0ul; j < S; ++j)
		{
			if (SCAN_BYTES[i + j] != D[j] && D[j] != -1)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return (uintptr_t)&SCAN_BYTES[i];
		}
	}
	return (uintptr_t)nullptr;
}
