#pragma once

namespace args_parse {

	class Arg {
	protected:
		const char* option;
		const char* longOption;
		const char* description;
		const char* operands = "";

		bool TryParseOption(const char* arg);
	public:
		Arg(const char* option, const char* longOption, const char* description = "");
		const char* GetDescription();
		virtual bool TryParse(const char* arg) = 0;
	};

}