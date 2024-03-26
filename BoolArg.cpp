#include "BoolArg.hpp"
#include <cctype>
#include <cstdlib>

using namespace args_parse;

BoolArg::BoolArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {};

bool BoolArg::IsDefined(const char* arg) {
	if (TryParseOption(arg)) {

		if (std::isdigit(*operands)) {
			auto num = atoi(operands);

			if (num == 0 || num == 1) {

				return true;
			}
		}
	}

	return false;
}

bool BoolArg::TryParse(const char* arg) {
	if (TryParseOption(arg)) {

		if (std::isdigit(*operands)) {
			auto num = atoi(operands);

			if (num == 0 || num == 1) {
				value = num == 1;

				return true;
			}
		}
	}

	return false;
}

bool BoolArg::GetValue() {
	return value;
}