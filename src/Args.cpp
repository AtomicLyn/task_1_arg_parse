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
	: AbstractArg(ArgumentType::Empty, option, longOption, description) {};

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


BoolArg::BoolArg(const char option, std::string longOption, std::string description)
	: AbstractArg(ArgumentType::Bool, option, longOption, description) {};

const bool BoolArg::GetValue() const {
	return value;
}

ParseResult BoolArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

	value = num == 1;
	isDefined = true;

	return ParseResult::Ok();
}

ParseResult BoolArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

	value = num == 1;
	isDefined = true;

	return ParseResult::Ok();
}


IntArg::IntArg(std::unique_ptr<Validator<int>> validator, const char option, std::string longOption, std::string description)
	: validator{ std::move(validator) }, AbstractArg(ArgumentType::Int, option, longOption, description) {};

const int IntArg::GetValue() const {
	return value;
}

ParseResult IntArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

	value = num;
	isDefined = true;

	return ParseResult::Ok();
}

ParseResult IntArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

	value = num;
	isDefined = true;

	return ParseResult::Ok();
}


StringArg::StringArg(std::unique_ptr<Validator<std::string>> validator, const char option, std::string longOption, std::string description)
	: validator{ std::move(validator) }, AbstractArg(ArgumentType::String, option, longOption, description) {};

std::string_view StringArg::GetValue() const {
	return value;
}

ParseResult StringArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

	value = operands;
	isDefined = true;

	return ParseResult::Ok();
}

ParseResult StringArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

	value = operands;
	isDefined = true;

	return ParseResult::Ok();
}


MultiBoolArg::MultiBoolArg(const char option, std::string longOption, std::string description)
	: AbstractArg(ArgumentType::MultiBool, option, longOption, description) {};

const std::vector<bool>& MultiBoolArg::GetValues() const {
	return values;
}

const int MultiBoolArg::GetCount() const {
	return values.size();
}

ParseResult MultiBoolArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

	values.push_back(num == 1);
	isDefined = true;

	return ParseResult::Ok();

}

ParseResult MultiBoolArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

	const auto num = atoi(operands.c_str());

	if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

	values.push_back(num == 1);
	isDefined = true;

	return ParseResult::Ok();
}


MultiIntArg::MultiIntArg(std::unique_ptr<Validator<int>> validator, const char option, std::string longOption, std::string description)
	: validator{ std::move(validator) }, AbstractArg(ArgumentType::MultiInt, option, longOption, description) {};

const std::vector<int>& MultiIntArg::GetValues() const {
	return values;
}

const int MultiIntArg::GetCount() const {
	return values.size();
}

ParseResult MultiIntArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + ": The option is found, but the value is not integer" });

	auto num = atoi(operands.c_str());

	if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

	values.push_back(num);
	isDefined = true;

	return ParseResult::Ok();
}

ParseResult MultiIntArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

	if (!isInteger(operands))
		return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + ": The option is found, but the value is not integer" });

	auto num = atoi(operands.c_str());

	if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

	values.push_back(num);
	isDefined = true;

	return ParseResult::Ok();
}


MultiStringArg::MultiStringArg(std::unique_ptr<Validator<std::string>> validator, const char option, std::string longOption, std::string description)
	: validator{ std::move(validator) }, AbstractArg(ArgumentType::MultiString, option, longOption, description) {};

const std::vector<std::string>& MultiStringArg::GetValues() const {
	return values;
}

const int MultiStringArg::GetCount() const {
	return values.size();
}

ParseResult MultiStringArg::ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

	values.push_back(operands);
	isDefined = true;

	return ParseResult::Ok();
}

ParseResult MultiStringArg::ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
	if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
	if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

	values.push_back(operands);
	isDefined = true;

	return ParseResult::Ok();
}