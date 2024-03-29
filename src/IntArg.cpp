#include "IntArg.hpp"
#include <cctype>
#include <cstdlib>

using namespace args_parse;

IntArg::IntArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Int;
};

int IntArg::GetValue() {
	return value;
}

bool IntArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (std::isdigit(*operands)) {
			value = atoi(operands);

			return isDefined = true;
		}
	}

	return false;
}

bool IntArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {

		if (std::isdigit(*operands)) {
			value = atoi(operands);

			return isDefined = true;
		}
	}

	return false;
}