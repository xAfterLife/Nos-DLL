#pragma once
#include <Windows.h>

#define CAN_READ_POINTER(x) if(this == NULL || this == nullptr) return nullptr;
#define CAN_READ(x) if(this == NULL || this == nullptr) return -1;
#define CAN_READ_BOOL(x) if(this == NULL || this == nullptr) return false;
#define CAN_READ_CHAR(x) if(this == NULL || this == nullptr) return DUMMY_TEXT;

// Created with ReClass.NET by KN4CK3R
// These structures contains only MINIMAL information needed to the RPC


class Label
{
private:
	char pad_0000[128]; //0x0000
	wchar_t* m_pText; //0x0080

public:
	int GetLen();
	wchar_t* GetText();
	bool HasText();
}; //Size: 0x0084


class IconInformation
{
private:
	char pad_0000[12]; //0x0000
	short m_sIconId; //0x000C

public:
	short GetId();
}; //Size: 0x000E

class PlayerIcon
{
private:
	char pad_0000[168]; //0x0000
	IconInformation* m_pIconInformation; //0x00A8

public:
	IconInformation* GetInformation();
}; //Size: 0x00AC

class CharacterInfo
{
private:
	char pad_0000[248]; //0x0000
	PlayerIcon* m_pPlayerIcon; //0x00F8
	char pad_00FC[24]; //0x00FC
	Label* m_pNickname; //0x0114
	Label* m_pLvl; //0x0118
	Label* m_pAwLvl; //0x011C

public:
	PlayerIcon* GetIcon();
	Label* GetNickname();
	Label* GetLvl();
	Label* GetAwLvl();
}; //Size: 0x0120

class TimespaceInformation
{
private:
	char pad_0000[24]; //0x0000
	bool m_bIsInTimespace; //0x0018

public:
	bool IsInTimespace();
}; //Size: 0x0019

class WaveTimer
{
private:
	char pad_0000[92]; //0x0000
	int m_iTimeToEnd; //0x005C

public:
	int GetTimeToEnd();
}; //Size: 0x0060

class MiniMap
{
private:
	char pad_0000[196]; //0x0000
	Label* m_pName; //0x00C4
	char pad_00C8[888]; //0x00C8

public:
	Label* GetName();
}; //Size: 0x0440

class Player
{
private:
	char pad_0000[165]; //0x0000
	bool m_bIsSitting; //0x00A5

public:
	bool IsSitting();
}; //Size: 0x00A6