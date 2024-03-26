#include "EmptyArg.hpp"
#include <iostream>

using namespace args_parse;

EmptyArg::EmptyArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Empty;
};

bool EmptyArg::IsDefined(const char* arg) {
	return TryParseOption(arg) && strlen(operands) == 0;
}

bool EmptyArg::TryParse(const char* arg) {
	return TryParseOption(arg) && strlen(operands) == 0;
}

