#include "MultiIntArg.hpp"
#include <cctype>
#include <cstdlib>

using namespace args_parse;

MultiIntArg::MultiIntArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Int;
};


bool MultiIntArg::Parse(const char* arg) {
	if (ParseOption(arg)) {

		if (std::isdigit(*operands)) {
			values.push_back(atoi(operands));

			return isDefined = true;
		}
	}

	return false;
}

bool MultiIntArg::ParseLong(const char* arg) {
	if (ParseLongOption(arg)) {

		if (std::isdigit(*operands)) {
			values.push_back(atoi(operands));

			return isDefined = true;
		}
	}

	return false;
}

std::vector<int> MultiIntArg::GetValues() {
	return values;
}