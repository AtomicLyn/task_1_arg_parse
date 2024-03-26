#include "Arg.hpp"
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace args_parse;

constexpr int optionSize = 1;

Arg::Arg(const char* option, const char* longOption, const char* description) {
	this->option = option;
	this->longOption = longOption;
	this->description = description;
}

bool Arg::TryParseOption(const char* arg) {
	if (*arg != '-') return false;

	const char* argWithoutDash = arg + 1;

	if (*argWithoutDash != '-') {
		if (strncmp(option, argWithoutDash, optionSize) == 0) {
			const char* argWithoutOption = argWithoutDash + 1;

			if (*argWithoutOption == '=') {
				const char* argWithoutOptionAndEq = argWithoutOption + 1;

				if (strlen(argWithoutOptionAndEq) != 0) {
					operands = argWithoutOptionAndEq;

					return true;
				}

				return false;
			}

			operands = argWithoutOption;

			return true;
		}
	}
	else {
		++argWithoutDash;

		int longOptionSize = strlen(longOption);

		if (strncmp(longOption, argWithoutDash, longOptionSize) == 0) {
			const char* argWithoutOption = argWithoutDash + longOptionSize;

			if (strlen(argWithoutOption) != 0) {
				if (*argWithoutOption == '=') {
					const char* argWithoutOptionAndEq = argWithoutOption + 1;

					if (strlen(argWithoutOptionAndEq) != 0) {
						operands = argWithoutOptionAndEq;

						return true;
					}

					return false;
				}

				return false;
			}

			operands = argWithoutOption;

			return true;
		}
	}

	return false;
}

const char* Arg::GetDescription() {
	return description;
}