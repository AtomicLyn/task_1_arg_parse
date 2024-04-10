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
		//static const std::string strExpr = "^[0-9]+([s]|[ms]|[us]|[ns])$";
		std::chrono::microseconds us;	
	public:
		ParseResult Parse(std::string_view operand) override {
			/// TODO: логика парсинга
			std::string input{ operand };
			std::stringstream ss{ input };
			int value;
			std::string unit;

			ss >> value >> unit;

			return ParseResult::Ok();
		}
		const long long Get() const override {
			return us.count();
		}
	};

}
