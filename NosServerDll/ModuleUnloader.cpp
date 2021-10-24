#include "ModuleUnloader.h"

#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

#include "Texts.h"
#include "Utilities.h"
#include "obfuscator.hpp"

ModuleUnloader::ModuleUnloader ()
{
	modules_ = Texts::Module_list;
}

std::vector<std::string> ModuleUnloader::CheckModules ()
{
	MODULEENTRY32 me32;

	auto* const H_MODULE_SNAP = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	if (H_MODULE_SNAP == INVALID_HANDLE_VALUE)
	{
		return modules_;
	}

	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(H_MODULE_SNAP, &me32))
	{
		CloseHandle(H_MODULE_SNAP);
		return modules_;
	}

	do
	{
		std::string lower_module = me32.szModule;
		std::for_each(lower_module.begin(), lower_module.end(), [](char& c)
		{
			c = tolower(c);
		});

		for (const auto& MODULE : modules_)
		{
			if (MODULE == lower_module)
				goto cnt;
		}
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibraryAndExitThread, GetModuleHandleA(lower_module.c_str()), 0, nullptr);
	cnt:;
	}
	while (Module32Next(H_MODULE_SNAP, &me32));

	CloseHandle(H_MODULE_SNAP);
	return modules_;
}

void ModuleUnloader::Print ()
{
	for (const auto& STR : modules_)
	{
		std::cout << STR << std::endl;
	}
}
