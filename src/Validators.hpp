#pragma once
#include "ParseResult.hpp"
#include <regex>

namespace args_parse {

	/// @brief Базовый класс валидатора Integer значений
	class IntValidator {
	public:
		virtual const ParseResult Check(const int value) const = 0;
	};

	/// @brief Базовый класс валидатора String значений
	class StringValidator {
	public:
		virtual const ParseResult Check(const std::string str) const = 0;
	};

	/// @brief Валидатор Bool значений
	class BoolValidator : public IntInRangeValidator {
	public:
		BoolValidator() : IntInRangeValidator(0, 1) {};
	};

	/// @brief Валидатор Integer значений в заданном диапазоне
	class IntInRangeValidator : public IntValidator {
		int min;
		int max;
	public:
		IntInRangeValidator(const int min, const int max) : min{ min }, max{ max } {};
		const ParseResult Check(const int value) const override {
			if (value < min) return ParseResult::Fail({ "In " + std::to_string(value) + ": value is less than [" + std::to_string(min) + ";" + std::to_string(max) + "]" });
			if (value > max) return ParseResult::Fail({ "In " + std::to_string(value) + ": value is greater than [" + std::to_string(min) + ";" + std::to_string(max) + "]" });
			return ParseResult::Ok();
		}
	};

	/// @brief Валидатор Bool значений
	class BoolValidator : public IntInRangeValidator {
	public:
		BoolValidator() : IntInRangeValidator(0, 1) {};
	};

	/// @brief Валидатор String значений для названий файлов
	class StringFileNameValidator : public StringValidator {
		const std::string strExpr = "^[a-z0-9-_]+[.][a-z]+$";
	public:
		const ParseResult Check(const std::string str) const override {
			if (!std::regex_match(str, std::regex(strExpr))) return ParseResult::Fail({ "In " + str + ": string is does not match |" + strExpr + "|" });
			return ParseResult::Ok();
		}
	};

	/// @brief Валидатор String значений для форматов файлов
	class StringFileFormatValidator : public StringValidator {
		const std::string strExpr = "^[*]+[.][a-z]+$";
	public:
		const ParseResult Check(const std::string str) const override {
			if (!std::regex_match(str, std::regex(strExpr))) return ParseResult::Fail({ "In " + str + ": string is does not match |"+ strExpr + "|"});
			return ParseResult::Ok();
		}
	};

}