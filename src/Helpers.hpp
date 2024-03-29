#pragma once
#include <string>

namespace args_parse {
	inline bool isInteger(std::string_view s)
	{
		if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
		char* p;
		strtol(s.data(), &p, 10);
		return (*p == 0);
	}
}
