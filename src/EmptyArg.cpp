#include "EmptyArg.hpp"

using namespace args_parse;

EmptyArg::EmptyArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::Empty, option, longOption, description) {};

const bool EmptyArg::Parse(std::string_view arg) {

	if (ParseOption(arg)) {
		return isDefined = true;
	}

	return false;
}

const bool EmptyArg::ParseLong(std::string_view arg) {
	if (ParseOption(arg)) {
		return isDefined = true;
	}

	return false;
}

