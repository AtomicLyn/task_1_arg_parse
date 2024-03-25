#include "BoolArg.hpp"
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace args_parse;

BoolArg::BoolArg(const char* option, const char* longOption, const char* description) : Arg(option, longOption, description) {};

bool BoolArg::TryParse(const char* arg) {
	int optionSize = strlen(option);
	int longOptionSize = strlen(longOption);

	if (strncmp(option, arg, optionSize) == 0) {
		const char* argWithoutOption = arg + optionSize;

		if (std::isdigit(*argWithoutOption)) {
			int num = atoi(argWithoutOption);

			if (num == 0 || num == 1) {
				value = num == 1;

				return true;
			}
		}
	}
	else if (strncmp(longOption, arg, longOptionSize) == 0) {
		const char* argWithoutOption = arg + longOptionSize;

		if (*argWithoutOption == '=') {
			const char* argWithoutOptionAndEq = argWithoutOption + 1;

			if (isdigit(*argWithoutOptionAndEq)) {
				int num = atoi(argWithoutOptionAndEq);

				if (num == 0 || num == 1) {
					value = num == 1;
					return true;
				}
			}
		}
	}

	return false;
}

bool BoolArg::GetValue() {
	return value;
}