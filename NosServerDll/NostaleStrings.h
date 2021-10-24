#pragma once
#include <cstring>

#define NostaleStringA CEE0A93D0C5C4E2685BEA79AE341F130
#define NostaleStringW FF930A2B1FF549F2813F6FFE657C3F1D

struct CEE0A93D0C5C4E2685BEA79AE341F130
{
	char* M_buffer;
	size_t M_length;

	CEE0A93D0C5C4E2685BEA79AE341F130 (void) : M_buffer(nullptr), M_length(0) { }

	explicit CEE0A93D0C5C4E2685BEA79AE341F130 (const char* str) : M_buffer(nullptr), M_length(0)
	{
		this->Set(str);
	}

	~CEE0A93D0C5C4E2685BEA79AE341F130 (void)
	{
		delete[] this->M_buffer;
		this->M_buffer = nullptr;
	}

	// Returns the size of the string.
	size_t Len (void) const
	{
		return this->M_buffer != nullptr ? this->M_length : 0;
	}

	// Returns the string within the buffer.
	char* Get (void) const
	{
		return this->M_buffer != nullptr ? static_cast<char*>(this->M_buffer + 0x08) : nullptr;
	}

	// Sets the string buffer.
	void Set (const char* str)
	{
		delete[] this->M_buffer;

		this->M_length = strlen(str);
		this->M_buffer = new char[this->M_length + 8 + 1];

		*(unsigned int*)(this->M_buffer + 0x00) = 1;              // Reference Count
		*(unsigned int*)(this->M_buffer + 0x04) = this->M_length; // Length
		memcpy(this->M_buffer + 0x08, str, this->M_length);
		this->M_buffer[this->M_length + 0x08] = '\0';
	}
};

struct FF930A2B1FF549F2813F6FFE657C3F1D
{
	wchar_t* M_buffer;
	size_t M_length;

	FF930A2B1FF549F2813F6FFE657C3F1D (void) : M_buffer(nullptr), M_length(0) { }

	explicit FF930A2B1FF549F2813F6FFE657C3F1D (const wchar_t* str) : M_buffer(nullptr), M_length(0)
	{
		this->Set(str);
	}

	~FF930A2B1FF549F2813F6FFE657C3F1D (void)
	{
		if (this->M_buffer != nullptr)
			delete[] this->M_buffer;
		this->M_buffer = nullptr;
	}

	// Returns the size of the string.
	size_t Len (void) const
	{
		return this->M_buffer != nullptr ? this->M_length : 0;
	}

	// Returns the string within the buffer.
	wchar_t* Get (void) const
	{
		return this->M_buffer != nullptr ? (wchar_t*)((char*)this->M_buffer + 0x08) : nullptr;
	}

	// Sets the string buffer.
	void Set (const wchar_t* str)
	{
		if (this->M_buffer != nullptr)
			delete[] this->M_buffer;

		this->M_length = wcslen(str) * 2;
		this->M_buffer = new wchar_t[this->M_length + 8 + 1];

		*(unsigned int*)((char*)this->M_buffer + 0x00) = 1;              // Reference Count
		*(unsigned int*)((char*)this->M_buffer + 0x04) = this->M_length; // Length
		memcpy((char*)this->M_buffer + 0x08, str, this->M_length);
		*(wchar_t*)((char*)this->M_buffer + this->M_length + 0x08) = L'\0';
	}
};
