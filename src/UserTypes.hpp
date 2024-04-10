#pragma once

#include "ParseResult.hpp"
#include <chrono>

namespace args_parse {

	template<typename T>
	class UserType {
	public:
		virtual ParseResult Parse(std::string operand) = 0;
		virtual const T Get() const = 0;
	};

	class UserChrono : UserType<long long> {
		std::chrono::microseconds us;
	public:
		ParseResult Parse(std::string operand) override {
			/// TODO: логика парсинга

			return ParseResult::Ok();
		}
		const long long Get() const override {
			return us.count();
		}
	};

}
