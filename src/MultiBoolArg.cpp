#include "MultiBoolArg.hpp"
#include <cctype>
#include <cstdlib>

using namespace args_parse;

MultiBoolArg::MultiBoolArg(const char option, const char* longOption, const char* description) : Arg(option, longOption, description) {
	type = ArgumentType::MultiBool;
};

std::vector<bool> MultiBoolArg::GetValues() {
	return values;
}

bool MultiBoolArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (std::isdigit(*operands)) {
			auto num = atoi(operands);

			if (num == 0 || num == 1) {
				values.push_back(num == 1);

				return isDefined = true;
			}
		}
	}

	return false;
}

bool MultiBoolArg::ParseLong(std::string_view arg) {
	if (ParseLongOption(arg)) {

		if (std::isdigit(*operands)) {
			auto num = atoi(operands);

			if (num == 0 || num == 1) {
				values.push_back(num == 1);

				return isDefined = true;
			}
		}
	}

	return false;
}