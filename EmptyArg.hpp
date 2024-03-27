#pragma once

#include "Arg.hpp"
#include "ArgumentType.hpp"

namespace args_parse {

	class EmptyArg : public Arg {
	public:
		EmptyArg(const char option, const char* longOption, const char* description = "");
		bool TryParse(const char* arg) override;
		bool TryParseLong(const char* arg) override;
	};

}