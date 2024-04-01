#include "MultiIntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

MultiIntArg::MultiIntArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::MultiInt, option, longOption, description) {};

const std::vector<int> MultiIntArg::GetValues() {
	return values;
}

const bool MultiIntArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (isInteger(operands)) {
			values.push_back(atoi(operands.c_str()));

			return isDefined = true;
		}
	}

	return false;
}

const bool MultiIntArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {

		if (isInteger(operands)) {
			values.push_back(atoi(operands.c_str()));

			return isDefined = true;
		}
	}

	return false;
}