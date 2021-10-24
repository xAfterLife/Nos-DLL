#pragma once
#include <vector>

#define FindDmaAddy AF5366DEAA51422DAA81491C139493C4
#define GamePointer E8364A8B8E8F47D2B819E0AA330D9E66
#define GetValue A2EF0200EB57433CB2A1F5C132244439

inline uintptr_t AF5366DEAA51422DAA81491C139493C4 (const uintptr_t ptr, const std::vector<unsigned int>& offsets)
{
	auto addr = ptr;
	for (auto offset : offsets)
	{
		addr = *(uintptr_t*)addr;
		addr += offset;
	}
	return addr;
}

template <class T>
struct E8364A8B8E8F47D2B819E0AA330D9E66 final
{
	T* Address;

	T const& A2EF0200EB57433CB2A1F5C132244439 () const
	{
		return *Address;
	}

	E8364A8B8E8F47D2B819E0AA330D9E66 (const uintptr_t base, const std::vector<unsigned int>& offsets)
	{
		Address = (T*)FindDmaAddy(base, offsets);
	}
};
