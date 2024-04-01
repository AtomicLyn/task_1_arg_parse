#pragma once

#include "ArgumentType.hpp"
#include <string>
#include <string_view>

namespace args_parse {
	
	/**
	* @brief Базовый абстрактный класс для всех аргументов
	*/
	class Arg {
		const ArgumentType type;
		char option;
		const std::string longOption;
		const std::string description;	

	protected:
		std::string operands;
		bool isDefined = false;

		[[nodiscard]] const bool ParseOption(std::string_view arg);
		[[nodiscard]] const bool ParseLongOption(std::string_view arg);
	public:
		Arg(ArgumentType type, const char option, const std::string longOption,  std::string description = "");
		virtual ~Arg();
		const char GetOption() const;
		const std::string GetLongOption() const;
		const std::string GetDescription() const;
		[[nodiscard]] const ArgumentType GetType() const;
		[[nodiscard]] const bool IsDefined() const;
		[[nodiscard]] virtual const bool Parse(std::string_view arg) = 0;
		[[nodiscard]] virtual const bool ParseLong(std::string_view arg) = 0;
		
	};

}