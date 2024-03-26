#pragma once

#include "Arg.hpp"

namespace args_parse {

	class BoolArg : public Arg {
	private:
		bool value = false;
	public: 
		BoolArg(const char option, const char* longOption, const char* description = "");
		bool GetValue();
		bool IsDefined(const char* arg) override;
		bool TryParse(const char* option) override;
	};

}