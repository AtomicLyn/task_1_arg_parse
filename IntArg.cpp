#include "IntArg.hpp"
#include <cctype>
#include <cstdlib>

using namespace args_parse;

IntArg::IntArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Int;
};

bool IntArg::IsDefined(const char* arg) {
	if (TryParseOption(arg)) {

		if (std::isdigit(*operands)) {

			return true;
		}
	}

	return false;
}


bool IntArg::TryParse(const char* arg) {
	if (TryParseOption(arg)) {

		if (std::isdigit(*operands)) {
			value = atoi(operands);

			return true;
		}
	}

	return false;
}

int IntArg::GetValue() {
	return value;
}