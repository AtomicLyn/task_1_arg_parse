#include "EmptyArg.hpp"

using namespace args_parse;

EmptyArg::EmptyArg(const char option, std::string longOption, std::string description) : Arg(option, longOption, description) {
	type = ArgumentType::Empty;
};

bool EmptyArg::Parse(std::string_view arg) {

	if (ParseOption(arg)) {
		return isDefined = true;
	}

	return false;
}

bool EmptyArg::ParseLong(std::string_view arg) {

	if (ParseOption(arg)) {
		return isDefined = true;
	}

	return false;
}

