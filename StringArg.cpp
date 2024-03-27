#include "StringArg.hpp"

using namespace args_parse;

StringArg::StringArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::String;
};

std::string StringArg::GetValue() {
	return value;
}


bool StringArg::Parse(const char* arg) {
	if (ParseOption(arg)) {
		value = std::string(operands);

		return isDefined = true;
	}

	return false;
}

bool StringArg::ParseLong(const char* arg) {
	if (ParseLongOption(arg)) {
		value = std::string(operands);

		return isDefined = true;
	}

	return false;
}

