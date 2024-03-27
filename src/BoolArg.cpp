#include "BoolArg.hpp"
#include <cctype>
#include <cstdlib>

using namespace args_parse;

BoolArg::BoolArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Bool;
};

bool BoolArg::GetValue() {
	return value;
}

bool BoolArg::Parse(const char* arg) {
	if (ParseOption(arg)) {

		if (std::isdigit(*operands)) {
			auto num = atoi(operands);

			if (num == 0 || num == 1) {
				value = num == 1;

				return isDefined = true;
			}
		}
	}

	return false;
}

bool BoolArg::ParseLong(const char* arg) {
	if (ParseLongOption(arg)) {

		if (std::isdigit(*operands)) {
			auto num = atoi(operands);

			if (num == 0 || num == 1) {
				value = num == 1;

				return isDefined = true;
			}
		}
	}

	return false;
}