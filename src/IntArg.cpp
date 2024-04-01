#include "IntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

IntArg::IntArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Int, option, longOption, description) {};

const int IntArg::GetValue() {
	return value;
}

const bool IntArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (isInteger(operands)) {
			value = atoi(operands.c_str());

			return isDefined = true;
		}
	}

	return false;
}

const bool IntArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {

		if (isInteger(operands)) {
			value = atoi(operands.c_str());

			return isDefined = true;
		}
	}

	return false;
}