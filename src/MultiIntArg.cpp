#include "MultiIntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

MultiIntArg::MultiIntArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::MultiInt;
};

std::vector<int> MultiIntArg::GetValues() {
	return values;
}

bool MultiIntArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (isInteger(operands)) {
			values.push_back(atoi(&operands[0]));

			return isDefined = true;
		}
	}

	return false;
}

bool MultiIntArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {

		if (isInteger(operands)) {
			values.push_back(atoi(&operands[0]));

			return isDefined = true;
		}
	}

	return false;
}