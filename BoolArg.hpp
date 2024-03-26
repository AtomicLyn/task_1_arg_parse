#pragma once

#include "Arg.hpp"

namespace args_parse {

	class BoolArg : Arg {
	private:
		bool value = false;
	public: 
		BoolArg(const char* option, const char* longOption, const char* description = "");
		bool GetValue();
		bool TryParse(const char* option) override;
	};

}