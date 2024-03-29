#include "IntArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

IntArg::IntArg(const char option, std::string longOption, std::string description) : Arg(option, longOption, description) {
	type = ArgumentType::Int;
};

int IntArg::GetValue() {
	return value;
}

bool IntArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (isInteger(operands)) {
			value = atoi(&operands[0]);

			return isDefined = true;
		}
	}

	return false;
}

bool IntArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {

		if (isInteger(operands)) {
			value = atoi(&operands[0]);

			return isDefined = true;
		}
	}

	return false;
}