#pragma once
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#define Split DE5FE03B108A4248BCB45B1EDBF35EF2
#define Utils DE5ZE09B108A4248BCB45B1EDBF35EF2
#define Append DEEZ509B1A084248BCB45B1EDB5F3EF2

class DE5ZE09B108A4248BCB45B1EDBF35EF2
{
public:
	template <typename Out>
	static void DE5FE03B108A4248BCB45B1EDBF35EF2 (const std::string& s, const char delim, Out result)
	{
		std::istringstream iss(s);
		std::string item;
		while (std::getline(iss, item, delim))
		{
			*result++ = item;
		}
	}

	static std::vector<std::string> DE5FE03B108A4248BCB45B1EDBF35EF2 (const std::string& s, const char delim)
	{
		std::vector<std::string> elems;
		DE5FE03B108A4248BCB45B1EDBF35EF2(s, delim, std::back_inserter(elems));
		return elems;
	}

	static std::string DEEZ509B1A084248BCB45B1EDB5F3EF2 (const std::string& s, const std::string& s2)
	{
		return s + s2;
	}
};
