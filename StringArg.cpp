#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {};

bool StringArg::TryParse(const char* arg) {
	if (TryParseOption(arg)) {
		value = std::string(operands);

		return true;
	}

	return false;
}

std::string StringArg::GetValue() {
	return value;
}