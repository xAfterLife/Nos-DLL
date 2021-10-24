#include "packet_logger.h"
#include <iostream>

#include "Discord.h"
#include "Utilities.h"
#include "VerificationHelper.h"
#include "fpsbreaker.h"
#include "hooking.h"
#include "memscan.h"
#include "NostaleStrings.h"

static LPVOID Lpv_send_addy;
static LPVOID Lpv_recv_addy;
static LPVOID Lpv_packet_this;
static PacketLogger* Instance;

#pragma managed(push, off)
void PacketLogger::CustomSend()
{
	char const* sz_packet;

	_asm { MOV sz_packet, EDX }

	if (strncmp(static_cast<char const*>(sz_packet), Texts::Fps.c_str(), strlen(Texts::Fps.c_str())) == 0)
	{
		auto fps = FpsBreaker::GetInstance();
		auto packetsplit = Utils::Split(sz_packet, ' ');

		if (packetsplit.back() == "reset")
		{
			fps.ResetFpsLimit();
			Instance->ReceivePacket(Utils::Append(Texts::Fps_set, std::to_string(fps.GetFpsLimit())).c_str());
		}
		else
		{
			auto tmp_fps = atoi(packetsplit.back().c_str());
			if (tmp_fps < 10) tmp_fps = 10;
			if (tmp_fps > 1000) tmp_fps = 1000;
			auto fps_value = static_cast<int>(1000 / static_cast<int>(1000 / tmp_fps));
			fps.SetFpsLimit(fps_value);
			Instance->ReceivePacket(Utils::Append(Texts::Fps_set, std::to_string(fps_value)).c_str());
		}
	}

	if (strncmp(static_cast<char const*>(sz_packet), Texts::Rpc.c_str(), strlen(Texts::Rpc.c_str())) == 0)
	{
		Discord::SetDetails(sz_packet + strlen(Texts::Rpc.c_str()));
	}
}

void PacketLogger::CustomRecv()
{
	char const* sz_packet;

	_asm { MOV sz_packet, EDX }

	if (strncmp(static_cast<char const*>(sz_packet), Texts::Ok.c_str(), strlen(Texts::Ok.c_str())) == 0)
	{
		Instance->SendPacket(Texts::IsLauncher.c_str());
	}
}

void PacketLogger::CustomSendLog()
{
	char const* sz_packet;

	_asm { MOV sz_packet, EDX }

	std::cout << Texts::Prefix_send << sz_packet << std::endl;
}

void PacketLogger::CustomRecvLog()
{
	char const* sz_packet;

	_asm { MOV sz_packet, EDX }

	std::cout << Texts::Prefix_recv << sz_packet << std::endl;
}

void PacketLogger::SendPacket(char const* szPacket)
{
	NostaleStringA str(static_cast<char const*>(szPacket));
	auto* packet = str.Get();

	_asm
	{
		MOV EAX, DWORD PTR DS : [Lpv_packet_this]
		MOV EAX, DWORD PTR DS : [EAX]
		MOV EAX, DWORD PTR DS : [EAX]
		MOV EDX, packet
		CALL Lpv_send_addy
	}
}

void PacketLogger::ReceivePacket(char const* szPacket)
{
	NostaleStringA str(szPacket);
	auto* packet = str.Get();

	_asm
	{
		MOV EAX, DWORD PTR DS : [Lpv_packet_this]
		MOV EAX, DWORD PTR DS : [EAX]
		MOV EAX, DWORD PTR DS : [EAX]
		MOV EAX, [EAX + 0x34]
		MOV EDX, packet
		CALL Lpv_recv_addy
	}
}

void PacketLogger::AddPrint()
{
	if (printToConsole_ != TRUE)
		return;

	UnhookSend();
	UnhookRecv();

	AllocConsole();
	freOut_ = freopen("CONOUT$", "w", stdout);

	HookSend();
	HookRecv();
}

void PacketLogger::RemovePrint()
{
	if (printToConsole_ != false)
		return;

	UnhookSend();
	UnhookRecv();

	auto* const CONSOLE_WINDOW = GetConsoleWindow();
	FreeConsole();
	PostMessage(CONSOLE_WINDOW, WM_CLOSE, 0, 0);
	CloseHandle(freOut_);

	HookSend();
	HookRecv();
}
#pragma managed(pop)

PacketLogger::PacketLogger()
{
	Instance = this;
}

PacketLogger::PacketLogger(const BOOL logger)
{
	Instance = this;
	printToConsole_ = logger;
	AllocConsole();
	freOut_ = freopen("CONOUT$", "w", stdout);
}

BOOL PacketLogger::StartLogger()
{
	return FindAddresses() && HookSend() && HookRecv();
}

BOOL PacketLogger::StopLogger() const
{
	return UnhookSend() && UnhookRecv();
}

BOOL PacketLogger::FindAddresses()
{
	Lpv_send_addy = Memscan::FindPattern(sendPattern_, sendMask_);
	Lpv_recv_addy = Memscan::FindPattern(recvPattern_, recvMask_);

	const auto P_THIS_PACKET = reinterpret_cast<DWORD_PTR>(Memscan::FindPattern(packetThisPattern_, packetThisMask_)) + 0x1;
	Lpv_packet_this = reinterpret_cast<LPVOID>(*reinterpret_cast<DWORD*>(P_THIS_PACKET));

	return Lpv_send_addy && Lpv_recv_addy && Lpv_packet_this;
}

BOOL PacketLogger::HookSend() const
{
	return Hooking::HookFunction(Lpv_send_addy, printToConsole_ ? CustomSendLog : CustomSend);
}

BOOL PacketLogger::HookRecv() const
{
	return Hooking::HookFunction(Lpv_recv_addy, printToConsole_ ? CustomRecvLog : CustomRecv);
}

BOOL PacketLogger::UnhookSend() const
{
	return Hooking::UnhookFunction(Lpv_send_addy);
}

BOOL PacketLogger::UnhookRecv() const
{
	return Hooking::UnhookFunction(Lpv_recv_addy);
}
