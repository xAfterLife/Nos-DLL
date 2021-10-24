#pragma once
#include <string>
#include <ctime>
#include <process.h>

#include "Texts.h"

#define VerificationHelper F6F911859BFA41FD85485540F8B03504
#define GenerateVerification A1FFE0986EF54CC995927BE2FB00C149

class F6F911859BFA41FD85485540F8B03504
{
public:

	static std::string A1FFE0986EF54CC995927BE2FB00C149 (const int16_t checksum)
	{
		std::string tmp_s = Texts::Verify_inline;
		int16_t sum = 0;

		srand(static_cast<unsigned>(time(nullptr)) * _getpid());

		while (sum < checksum)
		{
			int8_t cur_rand = rand() % 10;
			if (cur_rand > static_cast<int8_t>(checksum - sum))
				cur_rand = static_cast<int8_t>(checksum - sum);

			tmp_s += std::to_string(cur_rand);
			sum += cur_rand;
		}

		return tmp_s;
	}
};
