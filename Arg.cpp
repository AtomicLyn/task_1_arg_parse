#include "Arg.hpp"
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace args_parse;

constexpr auto optionSize = 1;

Arg::Arg(const char option, const char* longOption, const char* description) {
	this->option = option;
	this->longOption = longOption;
	this->description = description;
}

Arg::~Arg() {}

char Arg::GetOption() {
	return option;
}

const char* Arg::GetLongOption() {
	return longOption;
}

const char* Arg::GetDescription() {
	return description;
}

ArgumentType Arg::GetType() {
	return type;
}

bool Arg::IsDefined() {
	return isDefined;
}

bool Arg::ParseOption(const char* argWithoutDash) {
	if (strncmp(&option, argWithoutDash, optionSize) == 0) {
		auto argWithoutOption = argWithoutDash + 1;

		if (*argWithoutOption == '=') {
			auto argWithoutOptionAndEq = argWithoutOption + 1;

			if (strlen(argWithoutOptionAndEq) != 0) {
				operands = argWithoutOptionAndEq;

				return true;
			}

			return false;
		}

		operands = argWithoutOption;

		return true;
	}

	return false;
}

bool Arg::ParseLongOption(const char* argWithoutDash) {
	auto longOptionSize = strlen(longOption);

	if (strncmp(longOption, argWithoutDash, longOptionSize) == 0) {
		auto argWithoutOption = argWithoutDash + longOptionSize;

		if (*argWithoutOption == '=') {
			auto argWithoutOptionAndEq = argWithoutOption + 1;

			operands = argWithoutOptionAndEq;

			return true;
		}

		operands = argWithoutOption;

		return true;
	}

	return false;
}

