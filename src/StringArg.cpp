#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::String, option, longOption, description) {};

std::string StringArg::GetValue() {
	return value;
}


bool StringArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {
		value = operands;

		return isDefined = true;
	}

	return false;
}

bool StringArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {
		value = operands;

		return isDefined = true;
	}

	return false;
}

