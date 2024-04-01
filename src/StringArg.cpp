#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::String, option, longOption, description) {};

const std::string StringArg::GetValue() {
	return value;
}


const bool StringArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {
		value = operands;

		return isDefined = true;
	}

	return false;
}

const bool StringArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {
		value = operands;

		return isDefined = true;
	}

	return false;
}

