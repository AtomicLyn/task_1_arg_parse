#include "MultiBoolArg.hpp"
#include "Helpers.hpp"

using namespace args_parse;

MultiBoolArg::MultiBoolArg(const char option, std::string longOption, std::string description) : Arg(ArgumentType::MultiBool, option, longOption, description) {};

std::vector<bool> MultiBoolArg::GetValues() {
	return values;
}

bool MultiBoolArg::Parse(std::string_view arg) {
	if (ParseOption(arg)) {

		if (isInteger(operands)) {
			auto num = atoi(operands.c_str());

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

		if (isInteger(operands)) {
			auto num = atoi(operands.c_str());

			if (num == 0 || num == 1) {
				values.push_back(num == 1);

				return isDefined = true;
			}
		}
	}

	return false;
}