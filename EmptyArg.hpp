#pragma once

#include "Arg.hpp"

namespace args_parse {

	class EmptyArg : Arg {
	public:
		EmptyArg(const char option, const char* longOption, const char* description = "");
		bool TryParse(const char* arg) override;
	};

}