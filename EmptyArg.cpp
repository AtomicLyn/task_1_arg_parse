#include "EmptyArg.hpp"
#include <iostream>

using namespace args_parse;

EmptyArg::EmptyArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::Empty;
};

bool EmptyArg::TryParse(const char* arg) {
	return TryParseOption(arg) && strlen(operands) == 0;
}

bool EmptyArg::TryParseLong(const char* arg) {
	return TryParseLongOption(arg) && strlen(operands) == 0;
}

