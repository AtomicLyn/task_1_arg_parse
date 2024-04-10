#pragma once

#include "ParseResult.hpp"
#include <chrono>
#include <regex>
#include <sstream>

namespace args_parse {

	template<typename T>
	class UserType {
	public:
		virtual ParseResult Parse(std::string_view operand) = 0;
		virtual const T Get() const = 0;
	};

	class UserChrono : UserType<long long> {
		const std::string strExpr = "^[0-9]+(s|ms|us|ns)$";
		std::chrono::microseconds us;	
	public:
		ParseResult Parse(std::string_view operand) override {
			std::string input{ operand };

			if (!std::regex_match(input, std::regex(strExpr))) 
				return ParseResult::Fail({ "In " + std::string(operand) + " : operand is not chrono literal (" + strExpr + ")" });

			std::stringstream ss{ input };

			long long value;
			std::string unit;

			ss >> value >> unit;

			if (unit == "s") {
				auto seconds = std::chrono::seconds(value);
				us = std::chrono::microseconds(seconds);
			}
			else if (unit == "ms") {
				auto milliseconds = std::chrono::milliseconds(value);
				us = std::chrono::microseconds(milliseconds);
			}
			else if (unit == "us") {
				us = std::chrono::microseconds(us);
			}
			else if (unit == "ns") {
				auto nanoseconds = std::chrono::milliseconds(value);
				us = std::chrono::microseconds(nanoseconds);
			}
			else return ParseResult::Fail({ "In " + std::string(operand) + " : operand is not found in chrono literals (" + strExpr + ")" });

			return ParseResult::Ok();
		}
		const long long Get() const override {
			return us.count();
		}
	};

}
