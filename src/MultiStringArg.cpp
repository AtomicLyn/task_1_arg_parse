#include "MultiStringArg.hpp"

using namespace args_parse;

MultiStringArg::MultiStringArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::MultiString;
};

std::vector<std::string> MultiStringArg::GetValues() {
	return values;
}

bool MultiStringArg::Parse(const char* arg) {
	if (ParseOption(arg)) {
		values.push_back(std::string(operands));

		return isDefined = true;
	}

	return false;
}

bool MultiStringArg::ParseLong(const char* arg) {
	if (ParseLongOption(arg)) {
		values.push_back(std::string(operands));

		return isDefined = true;
	}

	return false;
}
