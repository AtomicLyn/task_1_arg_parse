#include "Arg.hpp"

using namespace args_parse;

bool Arg::ParseOption(std::string_view argWithoutDash) {
	if (argWithoutDash[0] == option) {

		if (argWithoutDash.size() > 1) {
			std::string_view argWithoutOption(&argWithoutDash[1]);

			if (argWithoutOption[0] == '=') {

				if (argWithoutOption.size() > 1) {
					std::string_view argWithoutOptionAndEq(&argWithoutOption[1]);

					operands = argWithoutOptionAndEq.data();

					return true;
				}

				return false;
			}

			operands = argWithoutOption.data();
		}

		return true;
	}

	return false;
}

bool Arg::ParseLongOption(std::string_view argWithoutDash) {
	const auto longOptionSize = longOption.size();

	if (argWithoutDash.find(longOption) == 0) {
		if (argWithoutDash.size() > longOptionSize) {
			std::string_view argWithoutOption(&argWithoutDash[longOptionSize]);

			if (argWithoutOption[0] == '=') {

				if (argWithoutOption.size() > 1) {
					std::string_view argWithoutOptionAndEq(&argWithoutOption[1]);

					operands = argWithoutOptionAndEq.data();

					return true;

				}

				return false;
			}
			
			operands = argWithoutOption.data();
		}

		return true;
	}

	return false;
}

Arg::Arg(const char option, std::string longOption, std::string description) : longOption{ longOption }, description{ description }, operands("") {
	this->option = option;
}

Arg::~Arg() {}

const char Arg::GetOption() {
	return option;
}

const std::string Arg::GetLongOption() {
	return longOption;
}

const std::string Arg::GetDescription() {
	return description;
}

const ArgumentType Arg::GetType() {
	return type;
}

const bool Arg::IsDefined() {
	return isDefined;
}



