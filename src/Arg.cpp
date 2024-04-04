#include "Arg.hpp"

using namespace args_parse;

const ParseResult Arg::ParseOption(std::string_view argWithoutDash) {
	currentArg = argWithoutDash;

	if (currentArg.find(option) != 0) return ParseResult::Fail();

	/// Препарсинг операндов
	if (currentArg.size() > 1) {
		std::string_view argWithoutOption(currentArg.c_str() + 1);

		if (argWithoutOption[0] != '=') operands = argWithoutOption;
		else {
			if (argWithoutOption.size() < 2) return ParseResult::Fail({ "In " + currentArg + ": Symbol '='  was found, but there is no value" });

			std::string_view argWithoutOptionAndEq(argWithoutOption.data() + 1);

			operands = argWithoutOptionAndEq;
		}

	}

	return ParseResult::Ok();
}

const std::pair<ParseResult, int> Arg::ParseLongOption(std::string_view argWithoutDash) {
	currentArg = argWithoutDash;

	const auto longOptionSize = longOption.size();

	if (currentArg.find(longOption[0]) != 0) return { ParseResult::Fail(), 0 };

	auto matches = 1;
	/// Поиск количества совпавших символов
	for (; matches < longOption.size() && matches < currentArg.size(); matches++)
		if (currentArg[matches] != longOption[matches]) break;

	/// Сохранение остатка строки
	if (currentArg.size() > matches) operands = currentArg.c_str() + matches;

	return { ParseResult::Ok(), matches };
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



