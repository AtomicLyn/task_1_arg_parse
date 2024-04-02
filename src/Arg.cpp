#include "Arg.hpp"

using namespace args_parse;

const bool Arg::ParseOption(std::string_view argWithoutDash) {
	if (argWithoutDash.find(option) == 0) {

		if (argWithoutDash.size() > 1) {
			std::string_view argWithoutOption(argWithoutDash.data() + 1);

			if (argWithoutOption[0] == '=') {

				if (argWithoutOption.size() > 1) {
					std::string_view argWithoutOptionAndEq(argWithoutOption.data() + 1);

					operands = argWithoutOptionAndEq;

					return true;
				}

				return false;
			}

			operands = argWithoutOption;
		}

		return true;
	}

	return false;
}

const bool Arg::ParseLongOption(std::string_view argWithoutDash) {
	const auto longOptionSize = longOption.size();

	if (argWithoutDash.find(longOption) == 0) {

		if (argWithoutDash.size() > longOptionSize) {
			std::string_view argWithoutOption(&argWithoutDash[longOptionSize]);

			if (argWithoutOption[0] == '=') {

				if (argWithoutOption.size() > 1) {
					std::string_view argWithoutOptionAndEq(argWithoutOption.data() + 1);

					operands = argWithoutOptionAndEq;

					return true;
				}

				return false;
			}

			operands = argWithoutOption;
		}

		return true;
	}

	return false;
}

Arg::Arg(ArgumentType type, const char option, std::string longOption, std::string description) 
	: type{ type }, option{ option }, longOption{ longOption }, description{ description },  operands("") { }

Arg::~Arg() {}

const char Arg::GetOption() const {
	return option;
}

const std::string Arg::GetLongOption() const {
	return longOption;
}

const std::string Arg::GetDescription() const {
	return description;
}

const ArgumentType Arg::GetType() const {
	return type;
}

const bool Arg::IsDefined() const {
	return isDefined;
}



