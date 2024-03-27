#include "IntArg.hpp"
#include <cctype>
#include <cstdlib>

using namespace args_parse;

IntArg::IntArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Int;
};


bool IntArg::Parse(const char* arg) {
	if (ParseOption(arg)) {

		if (std::isdigit(*operands)) {
			value = atoi(operands);

			return isDefined = true;
		}
	}

	return false;
}

bool IntArg::ParseLong(const char* arg) {
	if (ParseLongOption(arg)) {

		if (std::isdigit(*operands)) {
			value = atoi(operands);

			return isDefined = true;
		}
	}

	return false;
}

int IntArg::GetValue() {
	return value;
}