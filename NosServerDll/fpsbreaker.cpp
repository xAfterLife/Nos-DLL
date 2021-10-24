#include "fpsbreaker.h"
#include "memscan.h"

FpsBreaker::FpsBreaker ()
{
	fpsLimit_ = *(int**)(static_cast<BYTE*>(Memscan::FindPattern((BYTE*)"\xA3\x00\x00\x00\x00\xEB\x0A\xA3\x00\x00\x00\x00\xEB\x0A", "x????xx")) + 1);
	oldLimit_ = *fpsLimit_;
}

void FpsBreaker::SetFpsLimit (const int value) const
{
	*fpsLimit_ = static_cast<int>(1000 / value);
}

void FpsBreaker::ResetFpsLimit () const
{
	*fpsLimit_ = oldLimit_;
}

int FpsBreaker::GetFpsLimit () const
{
	return static_cast<int>(1000 / *fpsLimit_);
}

int FpsBreaker::GetFpsTiming () const
{
	return *fpsLimit_;
}
