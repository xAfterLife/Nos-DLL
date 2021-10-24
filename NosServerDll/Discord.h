#pragma once
#include <string>
#include "obfuscator.hpp"

class Discord
{
	inline static time_t startTime_;
	inline static std::string serverName_ = OBFUSCATE("CrystalNos");
	inline static std::string rpcDetails_ = OBFUSCATE("Playing NosTale- What else?");
public:
	static void UpdateThread ();
	static void Initialize ();
	static void Update ();
	static void SetDetails (const std::string&);
};
