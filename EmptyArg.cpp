#include "EmptyArg.hpp"
#include <iostream>

using namespace args_parse;

EmptyArg::EmptyArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Empty;
};

bool EmptyArg::Parse(const char* arg) {

	if (ParseOption(arg)) {
		return isDefined = true;
	}

	return false;
}

bool EmptyArg::ParseLong(const char* arg) {

	if (ParseOption(arg)) {
		return isDefined = true;
	}

	return false;
}

