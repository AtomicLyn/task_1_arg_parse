#pragma once

#include "ParseResult.hpp"
#include <chrono>
#include <regex>

namespace args_parse {

	/**
	* @brief Пользовательский тип времени
	* Хранит значение микросекунд, переданных из аргумента
	* @warning Для пользовательских типов необходимо определять конструктор по умолчанию и реализацию функции ParseType
	*/
	class UserChrono {
		std::chrono::microseconds us;	
	public:
		UserChrono() = default;
		UserChrono(std::chrono::microseconds us) : us{ us } {}
		std::chrono::microseconds GetMicroseconds() const { return us; }
	};

	/**
	* @brief Шаблонная функция парсинга пользовательских типов
	* Выполняет полный парсинг операнда, переданного из аргумента
	* @param[in] userChrono ссылка на объект, хранящийся в SingleArg<T>
	* @param[in] operand строка операнда для парсинга
	*/
	inline ParseResult ParseType(UserChrono& userChrono, std::string_view operand) {
		static const std::string strExpr = "^[0-9]+(d|h|m|s|ms|us|ns)$";
		static const std::regex reg{ strExpr };
		std::string input{ operand };

		std::smatch matches;
		if (!std::regex_search(input, matches, reg))
			return ParseResult::Fail({ "In " + std::string(operand) + " : operand is not chrono literal ( " + strExpr + " )" });

		long long value = std::stoll(matches[0]);
		std::string unit = matches[1];

		std::chrono::microseconds us;

		if (unit == "d") {
			auto seconds = std::chrono::seconds(value);
			us = std::chrono::microseconds(seconds);
		}
		else if (unit == "h") {
			auto seconds = std::chrono::seconds(value);
			us = std::chrono::microseconds(seconds);
		}
		else if (unit == "m") {
			auto seconds = std::chrono::seconds(value);
			us = std::chrono::microseconds(seconds);
		}
		else if (unit == "s") {
			auto seconds = std::chrono::seconds(value);
			us = std::chrono::microseconds(seconds);
		}
		else if (unit == "ms") {
			auto milliseconds = std::chrono::milliseconds(value);
			us = std::chrono::microseconds(milliseconds);
		}
		else if (unit == "us") {
			us = std::chrono::microseconds(value);
		}
		else if (unit == "ns") {
			auto nanoseconds = std::chrono::milliseconds(value);
			us = std::chrono::microseconds(nanoseconds);
		}
		else return ParseResult::Fail({ "In " + std::string(operand) + " : operand is not found in chrono literals ( " + strExpr + " )" });

		userChrono = UserChrono{ us };

		return ParseResult::Ok();
	}

	inline ParseResult ParseType(bool& value, std::string_view operand) {
		if(!IsInteger(operand))
			return ParseResult::Fail({ "In " + std::string(operand) + " : The option is found, but the value is not bool" });

		auto num = std::stoi(operand.data());

		if(num != 0 && num != 1)
			return ParseResult::Fail({ "In " + std::string(operand) + " : The operand is not bool" });

		value = num;

		return ParseResult::Ok();
	}

	inline ParseResult ParseType(int& value, std::string_view operand) {
		if (!IsInteger(operand))
			return ParseResult::Fail({ "In " + std::string(operand) + " : The option is found, but the value is not integer" });

		value = std::stoi(operand.data());

		return ParseResult::Ok();
	}

	inline ParseResult ParseType(float& value, std::string_view operand) {
		if (!IsFloat(operand))
			return ParseResult::Fail({ "In " + std::string(operand) + " : The option is found, but the value is not float" });

		value = std::stof(operand.data());

		return ParseResult::Ok();
	}

	inline ParseResult ParseType(std::string& value, std::string_view operand) {
		value = operand;

		return ParseResult::Ok();
	}
}
