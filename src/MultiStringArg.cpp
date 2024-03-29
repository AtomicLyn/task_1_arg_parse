#include "MultiStringArg.hpp"

using namespace args_parse;

MultiStringArg::MultiStringArg(const char option, std::string longOption, std::string description) : Arg(option, longOption, description) {
	type = ArgumentType::MultiString;
};

std::vector<std::string> MultiStringArg::GetValues() {
	return values;
}

bool MultiStringArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {
		values.push_back(std::string(operands));

		return isDefined = true;
	}

	return false;
}

bool MultiStringArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {
		values.push_back(std::string(operands));

		return isDefined = true;
	}

	return false;
}

