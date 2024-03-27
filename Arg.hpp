#pragma once

#include "ArgumentType.hpp"

namespace args_parse {

	class Arg {
	protected:
		ArgumentType type;

		char option;
		const char* longOption;
		const char* description;
		const char* operands = "";

		bool TryParseOption(const char* arg);
		bool TryParseLongOption(const char* arg);
	public:
		Arg(const char option, const char* longOption, const char* description = "");
		virtual ~Arg();
		const char* GetDescription();
		ArgumentType GetType();
		virtual bool TryParse(const char* arg) = 0;
		virtual bool TryParseLong(const char* arg) = 0;
	};

}