#include "BoolArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

BoolArg::BoolArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Bool;
};

bool BoolArg::GetValue() {
	return value;
}

bool BoolArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (isInteger(operands)) {
			auto num = atoi(&operands[0]);

			if (num == 0 || num == 1) {
				value = num == 1;

				return isDefined = true;
			}
		}
	}

	return false;
}

bool BoolArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {

		if (isInteger(operands)) {
			auto num = atoi(&operands[0]);

			if (num == 0 || num == 1) {
				value = num == 1;

				return isDefined = true;
			}
		}
	}

	return false;
}