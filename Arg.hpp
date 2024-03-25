#pragma once

namespace args_parse {

	class Arg {
	protected:
		const char* option;
		const char* longOption;
		const char* description;
		const char* operands;

		Arg(const char* option, const char* longOption, const char* description = "");
		bool TryParseOption(const char* arg);
	public:
		const char* GetDescription();
	};

}