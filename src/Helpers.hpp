#pragma once
#include <string>
#include <sstream>

namespace args_parse {
	inline bool IsInteger(std::string_view s)
	{
		return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}
	inline bool IsFloat(const std::string s)
	{
		std::istringstream iss(s);
		float f;
		iss >> std::noskipws >> f;
		return iss.eof() && !iss.fail();
	}
}
