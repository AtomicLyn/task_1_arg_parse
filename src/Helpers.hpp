#pragma once
#include <string_view>

namespace args_parse {
	inline bool isInteger(std::string_view s)
	{
		return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}
}
