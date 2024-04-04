#include "Arg.hpp"

using namespace args_parse;

const ParseResult Arg::ParseOption(std::string_view argWithoutDash) {
	if (argWithoutDash.find(option) == 0) {

		/// Парсинг операндов
		if (argWithoutDash.size() > 1) {
			std::string_view argWithoutOption(argWithoutDash.data() + 1);

			if (argWithoutOption[0] == '=') {

				if (argWithoutOption.size() > 1) {
					std::string_view argWithoutOptionAndEq(argWithoutOption.data() + 1);

					operands = argWithoutOptionAndEq;
				}
				else return ParseResult::Fail({ "In " + std::string(argWithoutDash) + ": Symbol '='  was found, but there is no value" });

			}
			else operands = argWithoutOption;

		}

		return ParseResult::Ok();
	}

	return ParseResult::Fail();
}

const std::pair<ParseResult, int> Arg::ParseLongOption(std::string_view argWithoutDash) {
	const auto longOptionSize = longOption.size();

	if (argWithoutDash.find(longOption[0]) == 0) {
		auto matches = 1;

		/// Поиск количества совпавших символов
		for (; matches < longOption.size() && matches < argWithoutDash.size(); matches++) {
			if (argWithoutDash[matches] != longOption[matches]) break;
		}

		/// Парсинг операндов
		if (argWithoutDash.size() > matches) {
			std::string_view argWithoutOption(argWithoutDash.data() + matches);

			if (argWithoutOption[0] == '=') {

				if (argWithoutOption.size() > 1) {
					std::string_view argWithoutOptionAndEq(argWithoutOption.data() + 1);

					operands = argWithoutOptionAndEq;
				}
				else return std::make_pair(ParseResult::Fail({ "In " + std::string(argWithoutDash) + ": Symbol '='  was found, but there is no value" }), 0);

			}
			else operands = argWithoutOption;

		}

		return std::make_pair(ParseResult::Ok(), matches);
	}

	return std::make_pair(ParseResult::Fail(), 0);
}

Arg::Arg(ArgumentType type, const char option, std::string longOption, std::string description)
	: type{ type }, option{ option }, longOption{ longOption }, description{ description }, operands("") { }

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



