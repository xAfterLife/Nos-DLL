#include "Discord.h"
#include <Windows.h>
#include <iostream>


#include "Texts.h"
#include "Utilities.h"
#include "discord_rpc.h"

void Discord::UpdateThread ()
{
	while (true)
	{
		Update();
		Discord_RunCallbacks();
		Sleep(15000);
	}
}

void Discord::Initialize ()
{
	DiscordEventHandlers handle;
	startTime_ = time(nullptr);

	memset(&handle, 0, sizeof handle);
	Discord_Initialize(Texts::Discord_application_key.c_str(), &handle, 1, nullptr);
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)UpdateThread, nullptr, 0, nullptr);
}

void Discord::Update ()
{
	std::cout << "Discord::Update 1" << std::endl;
	Sleep(300);
	
	DiscordRichPresence discord_presence;
	memset(&discord_presence, 0, sizeof discord_presence);

	std::cout << "Discord::Update 2" << std::endl;
	Sleep(300);
	
	discord_presence.largeImageKey = Texts::Discord_image_key.c_str();
	discord_presence.largeImageText = serverName_.c_str(); //In Zukunft Spielername
	discord_presence.smallImageKey = Texts::Discord_logo_key.c_str();
	discord_presence.smallImageText = serverName_.c_str();

	std::cout << "Discord::Update 3" << std::endl;
	Sleep(300);
	
	discord_presence.details = rpcDetails_.c_str();
	discord_presence.state = serverName_.c_str();

	std::cout << "Discord::Update 4" << std::endl;
	Sleep(300);
	
	discord_presence.startTimestamp = startTime_;
	discord_presence.endTimestamp = 0;

	std::cout << "Discord::Update 5" << std::endl;
	Sleep(300);

	Discord_UpdatePresence(&discord_presence);

	std::cout << "Discord::Update 6" << std::endl;
	Sleep(300);
}

void Discord::SetDetails (const std::string& s)
{
	rpcDetails_ = s;
}
