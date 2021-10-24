#include "Structures.h"

wchar_t* DUMMY_TEXT = (wchar_t*)L"???";
PlayerIcon* CharacterInfo::GetIcon()
{
	CAN_READ_POINTER(CharacterInfo);
	return m_pPlayerIcon;
}

Label* CharacterInfo::GetNickname()
{
	CAN_READ_POINTER(CharacterInfo);
	return m_pNickname;
}

Label* CharacterInfo::GetLvl()
{
	CAN_READ_POINTER(CharacterInfo);
	return m_pLvl;
}

Label* CharacterInfo::GetAwLvl()
{
	CAN_READ_POINTER(CharacterInfo);
	return m_pAwLvl;
}

IconInformation* PlayerIcon::GetInformation()
{
	CAN_READ_POINTER(PlayerIcon);
	return m_pIconInformation;
}

short IconInformation::GetId()
{
	CAN_READ(IconInformation);
	return m_sIconId;
}

bool TimespaceInformation::IsInTimespace()
{
	CAN_READ_BOOL(TimespaceInformation);
	return m_bIsInTimespace;
}

int WaveTimer::GetTimeToEnd()
{
	CAN_READ(WaveTimer);
	return m_iTimeToEnd;
}

int Label::GetLen()
{
	if (HasText())
		return *(int*)(m_pText - 0x2);

	return -1;
}

wchar_t* Label::GetText()
{
	CAN_READ_CHAR(Label);
	return m_pText;
}

bool Label::HasText()
{
	CAN_READ_BOOL(Label);
	return m_pText != nullptr;
}

Label* MiniMap::GetName()
{
	CAN_READ_POINTER(MiniMap);
	return m_pName;
}

bool Player::IsSitting()
{
	CAN_READ_BOOL(Player);
	return m_bIsSitting;
}
