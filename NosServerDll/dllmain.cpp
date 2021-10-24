#include <Windows.h>
#include <algorithm>
#include <iostream>

#include "Discord.h"
#include "GamePointer.h"
#include "ModuleUnloader.h"
#include "Texts.h"
#include "Utilities.h"
#include "packet_logger.h"
#include "fpsbreaker.h"
#include "obfuscator.hpp"

#define START_UP F50DCD2760D5430CAC5A56528B544FAE
#define GET_MODULE F50DDEF760D5430ACC5A56322B544FAE

HMODULE Dll_handle;
std::string Module_name;

std::string F50DDEF760D5430ACC5A56322B544FAE (HMODULE)
{
	auto* const FILE_NAME = new TCHAR[_MAX_PATH];
	GetModuleFileName(Dll_handle, FILE_NAME, _MAX_PATH);

	auto lower_module = Utils::Split(FILE_NAME, '\\').back();
	std::for_each(lower_module.begin(), lower_module.end(), [](char& c)
	{
		c = tolower(c);
	});
	return lower_module;
}

DWORD WINAPI F50DCD2760D5430CAC5A56528B544FAE ()
{
	Texts::Initialize(Module_name);
	Discord::Initialize();

	auto module_unloader = ModuleUnloader();
	const auto HEALTH_POINTER = GamePointer<int>(0x0089DBE4, {0XC4, 0x48});
	//const auto HEALTH_POINTER = GamePointer<int>(0x008A6A88, { 0XC4, 0x48 });

	while (HEALTH_POINTER.Address == nullptr || HEALTH_POINTER.GetValue() == 100)
	{
		module_unloader.CheckModules();
		Sleep(15);
	}

	auto packet_logger = PacketLogger();
	packet_logger.StartLogger();

	const auto FPS_BREAKER = FpsBreaker::GetInstance();
	FPS_BREAKER.SetFpsLimit(142);

	packet_logger.ReceivePacket(Utils::Append(Texts::Fps_set, "142").c_str());
	packet_logger.ReceivePacket(Texts::Copyright_after_life.c_str());

	packet_logger.SendPacket(Texts::IsLauncher.c_str());

	while (true)
	{
		module_unloader.CheckModules();
		Sleep(100);
	}
}

BOOL APIENTRY DllMain (const HMODULE hModule, const DWORD ulReasonForCall, LPVOID lpReserved)
{
	if (ulReasonForCall == DLL_PROCESS_ATTACH)
	{
		Dll_handle = hModule;
		Module_name = GET_MODULE(Dll_handle);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)START_UP, nullptr, 0, nullptr);
	}
	return TRUE;
}
