#include "Arg.hpp"
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace args_parse;

Arg::Arg(const char* option, const char* longOption, const char* description) {
	this->option = option;
	this->longOption = longOption;
	this->description = description;
}

bool Arg::TryParseOption(const char* arg) {
	int optionSize = strlen(option);
	int longOptionSize = strlen(longOption);

	if (strncmp(option, arg, optionSize) == 0) {
		operands = arg + optionSize;

		return true;
	}
	else if (strncmp(longOption, arg, longOptionSize) == 0) {
		const char* argWithoutOption = arg + longOptionSize;

		if (strlen(argWithoutOption) != 0) {
			if (*argWithoutOption == '=') {
				operands = argWithoutOption + 1;

				return true;
			}

			return false;
		}

		return true;
	}

	return false;
}

const char* Arg::GetDescription() {
	return description;
}