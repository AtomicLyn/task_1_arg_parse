#pragma once

#include "Arg.hpp"

namespace args_parse {

	class IntArg : public Arg {
	private:
		int value = -1;
	public:
		IntArg(const char option, const char* longOption, const char* description = "");
		int GetValue();
		bool TryParse(const char* arg) override;
		bool TryParseLong(const char* arg) override;
	};

}