#pragma once
#include "ParseResult.hpp"
#include <regex>

namespace args_parse {

	/// @brief ������� ����� ���������� Integer ��������
	class IntValidator {
	public:
		virtual const ParseResult Check(const int value) const = 0;
	};

	/// @brief ������� ����� ���������� String ��������
	class StringValidator {
	public:
		virtual const ParseResult Check(const std::string str) const = 0;
	};

	/// @brief ��������� Integer �������� � ��������� ���������
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

	/// @brief ��������� Bool ��������
	class BoolValidator : public IntInRangeValidator {
	public:
		BoolValidator() : IntInRangeValidator(0, 1) {};
	};

	/// @brief ��������� String �������� ��� �������� ������
	class StringFileNameValidator : public StringValidator {
		const std::string strExpr = "^[a-z0-9-_]+[.][a-z]+";
	public:
		const ParseResult Check(const std::string str) const override {
			if (!std::regex_match(str, std::regex(strExpr))) ParseResult::Fail({ "In " + str + ": sting is does not match |" + strExpr + "|" });
			return ParseResult::Ok();
		}
	};

	/// @brief ��������� String �������� ��� �������� ������
	class StringFileFormatValidator : public StringValidator {
		const std::string strExpr = "^[a-z]+[.][a-z]+";
	public:
		const ParseResult Check(const std::string str) const override {
			if (!std::regex_match(str, std::regex(strExpr))) ParseResult::Fail({ "In " + str + ": sting is does not match |"+ strExpr + "|"});
			return ParseResult::Ok();
		}
	};

}