#pragma once

#include "ArgumentType.hpp"
#include <string>

namespace args_parse {
	
	/**
	* @brief Базовый абстрактный класс для всех аргументов
	*/
	class Arg {
		char option;
		const std::string longOption;
		const std::string description;
		const ArgumentType type;

	protected:
		std::string operands;
		bool isDefined = false;

		bool ParseOption(std::string_view arg);
		bool ParseLongOption(std::string_view arg);
	public:
		Arg(ArgumentType type, const char option, const std::string longOption,  std::string description = "");
		virtual ~Arg();
		const char GetOption();
		const std::string GetLongOption();
		const std::string GetDescription();
		const ArgumentType GetType();
		const bool IsDefined();
		virtual bool Parse(std::string_view arg) = 0;
		virtual bool ParseLong(std::string_view arg) = 0;
		
	};

}