#include "MultiStringArg.hpp"

using namespace args_parse;

MultiStringArg::MultiStringArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::MultiString, option, longOption, description) {};

const std::vector<std::string> MultiStringArg::GetValues() {
	return values;
}

const int MultiStringArg::GetCount() {
	return values.size();
}

const bool MultiStringArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {
		values.push_back(operands);

		return isDefined = true;
	}

	return false;
}

const bool MultiStringArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {
		values.push_back(operands);

		return isDefined = true;
	}

	return false;
}

