#pragma once

#include "Arg.hpp"

namespace args_parse {

	class BoolArg : Arg {
	private:
		bool value = false;
	public: 
		BoolArg(const char* option, const char* longOption, const char* description = "");
		bool TryParse(const char* arg);
		bool GetValue();
	};

}