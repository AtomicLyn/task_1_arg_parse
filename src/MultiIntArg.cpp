#include "MultiIntArg.hpp"
#include <cctype>
#include <cstdlib>

using namespace args_parse;

MultiIntArg::MultiIntArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::MultiInt;
};

std::vector<int> MultiIntArg::GetValues() {
	return values;
}

bool MultiIntArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (std::isdigit(*operands)) {
			values.push_back(atoi(operands));

			return isDefined = true;
		}
	}

	return false;
}

bool MultiIntArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {

		if (std::isdigit(*operands)) {
			values.push_back(atoi(operands));

			return isDefined = true;
		}
	}

	return false;
}