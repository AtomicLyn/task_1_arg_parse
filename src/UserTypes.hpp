#pragma once

#include "ParseResult.hpp"
#include <chrono>
#include <regex>
#include <sstream>

namespace args_parse {

	class UserChrono {
		std::chrono::microseconds us;	
	public:
		UserChrono() = default;
		UserChrono(std::chrono::microseconds us) : us{ us } {}
		std::chrono::microseconds GetMicroseconds() const { return us; }
	};

	template<typename T>
	std::enable_if_t<std::is_same_v<T, UserChrono>, ParseResult>
	ParseUserType(T& userChrono, std::string_view operand) {
		const std::string strExpr = "^[0-9]+(d|h|m|s|ms|us|ns)$";
		std::string input{ operand };

		if (!std::regex_match(input, std::regex(strExpr)))
			return ParseResult::Fail({ "In " + std::string(operand) + " : operand is not chrono literal (" + strExpr + ")" });

		std::stringstream ss{ input };

		long long value;
		std::string unit;

		ss >> value >> unit;

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
		else return ParseResult::Fail({ "In " + std::string(operand) + " : operand is not found in chrono literals (" + strExpr + ")" });

		userChrono = UserChrono{ us };

		return ParseResult::Ok();
	}
}
