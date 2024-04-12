#pragma once
#include "ParseResult.hpp"
#include <regex>

namespace args_parse {

	/// @brief Базовый класс валидатора Integer значений
	template<typename T>
	class Validator {
	public:
		virtual ~Validator() = default;
		[[nodiscard]] virtual ParseResult Check(const T value) const = 0;
	};

	/// @brief Валидатор Integer значений в заданном диапазоне
	template<typename T = int>
	class InRangeValidator : public Validator<T> {
		T min;
		T max;
	public:
		InRangeValidator(const T min, const T max) : min{ min }, max{ max } {};
		ParseResult Check(const T value) const override {
			if (value < min) return ParseResult::Fail({ "In " + std::to_string(value) + ": value is less than [" + std::to_string(min) + ";" + std::to_string(max) + "]" });
			if (value > max) return ParseResult::Fail({ "In " + std::to_string(value) + ": value is greater than [" + std::to_string(min) + ";" + std::to_string(max) + "]" });
			return ParseResult::Ok();
		}
	};

	/// @brief Валидатор Bool значений
	class BoolValidator : public InRangeValidator<unsigned short> {
	public:
		BoolValidator() : InRangeValidator{ 0, 1 } {};
	};

	/// @brief Валидатор String значений для названий файлов
	template<typename T = std::string>
	class FileNameValidator : public Validator<T> {
		const std::string strExpr = "^[a-z0-9-_]+[.][a-z]+$";
	public:
		ParseResult Check(const T str) const override {
			if (!std::regex_match(str, std::regex(strExpr))) return ParseResult::Fail({ "In " + str + ": string is does not match | " + strExpr + " |" });
			return ParseResult::Ok();
		}
	};

	/// @brief Валидатор String значений для форматов файлов
	template<typename T = std::string>
	class FileFormatValidator : public Validator<T> {
		const std::string strExpr = "^[*]+[.][a-z]+$";
	public:
		ParseResult Check(const T str) const override {
			if (!std::regex_match(str, std::regex(strExpr))) return ParseResult::Fail({ "In " + str + ": string is does not match | "+ strExpr + " |"});
			return ParseResult::Ok();
		}
	};

}