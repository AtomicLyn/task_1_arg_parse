#include "Args.hpp"
#include "Helpers.hpp"

using namespace args_parse;

ParseResult AbstractArg::CheckOperand(std::optional<std::string> nextArg, bool& usedNextArg) {
	if (operands.empty() && !nextArg.has_value()) return ParseResult::Fail({ "In " + currentArg + " : An operand was expected" });
	if (operands[0] == '=' && operands.size() < 2) return ParseResult::Fail({ "In " + currentArg + " : Symbol '='  was found, but there is no value" });

	if (operands.empty()) {
		operands = nextArg.value();
		usedNextArg = true;
	}

	if (operands[0] == '=') operands = operands.substr(1);

	return ParseResult::Ok();
}

ParseResult AbstractArg::CheckLongOperand(std::optional<std::string> nextArg, bool& usedNextArg) {
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

ParseResult AbstractArg::ParseOption(std::string_view argWithoutDash) {
	currentArg = argWithoutDash;

	if (currentArg.find(option) != 0) return ParseResult::Fail();

	if (currentArg.size() > 1) operands = currentArg.substr(1);
	else operands.clear();

	return ParseResult::Ok();
}

const std::pair<ParseResult, int> AbstractArg::ParseLongOption(std::string_view argWithoutDash) {
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

AbstractArg::AbstractArg(ArgumentType type, const char option, std::string longOption, std::string description)
	: type{ type }, option{ option }, longOption{ longOption }, description{ description }, operands("") { }

AbstractArg::~AbstractArg() = default;

const char AbstractArg::GetOption() const {
	return option;
}

std::string_view AbstractArg::GetLongOption() const {
	return longOption;
}

std::string_view AbstractArg::GetDescription() const {
	return description;
}

const ArgumentType AbstractArg::GetType() const {
	return type;
}

const bool AbstractArg::IsDefined() const {
	return isDefined;
}


EmptyArg::EmptyArg(const char option, std::string longOption, std::string description) 
	: AbstractArg(ArgumentType::Empty, option, std::move(longOption), std::move(description)) {};

ParseResult EmptyArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (!operands.empty())
		if (operands[0] == '=')
			return ParseResult::Fail({ "In " + currentArg + " : Symbol '=' in EmptyArg was not expected" });

	isDefined = true;

	return ParseResult::Ok();
}

ParseResult EmptyArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (!operands.empty()) return ParseResult::Fail({ "In " + currentArg + " : The operand in EmptyArg was not expected" });

	isDefined = true;

	return ParseResult::Ok();
}