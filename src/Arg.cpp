#include "Arg.hpp"

using namespace args_parse;

const ParseResult Arg::CheckOperand(std::optional<std::string> nextArg, bool& usedNextArg) {
	if (operands.empty() && !nextArg.has_value()) return ParseResult::Fail({ "In " + currentArg + " : An operand was expected" });
	if (operands[0] == '=' && operands.size() < 2) return ParseResult::Fail({ "In " + currentArg + " : Symbol '='  was found, but there is no value" });

	if (operands.empty()) {
		operands = nextArg.value();
		usedNextArg = true;
	}

	if (operands[0] == '=') operands = operands.substr(1);

	return ParseResult::Ok();
}

const ParseResult Arg::CheckLongOperand(std::optional<std::string> nextArg, bool& usedNextArg) {
	if (!operands.empty()) {
		if (operands[0] != '=')
			return ParseResult::Fail({ "In " + currentArg + " : Symbol '=' or space between option and operand was not found" });
		if (operands.size() < 2)
			return ParseResult::Fail({ "In " + currentArg + " : Symbol '='  was found, but there is no value" });
	}
	if (operands.empty() && !nextArg.has_value())
		return ParseResult::Fail({ "In " + currentArg + " : An operand was expected" });

	if (!operands.empty()) operands = operands.substr(1);
	else {
		operands = nextArg.value();
		usedNextArg = true;
	}

	return ParseResult::Ok();
}

const ParseResult Arg::ParseOption(std::string_view argWithoutDash) {
	currentArg = argWithoutDash;

	if (currentArg.find(option) != 0) return ParseResult::Fail();

	if (currentArg.size() > 1) operands = currentArg.substr(1);
	else operands.clear();

	return ParseResult::Ok();
}

const std::pair<ParseResult, int> Arg::ParseLongOption(std::string_view argWithoutDash) {
	currentArg = argWithoutDash;

	if (currentArg.find(longOption[0]) != 0) return { ParseResult::Fail(), 0 };

	auto matches = 1;
	/// Поиск количества совпавших символов
	for (; matches < longOption.size() && matches < currentArg.size(); matches++)
		if (currentArg[matches] != longOption[matches]) break;

	/// Сохранение остатка строки
	if (currentArg.size() > matches) operands = currentArg.substr(matches);
	else operands.clear();

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



