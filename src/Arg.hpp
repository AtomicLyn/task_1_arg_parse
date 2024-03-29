#pragma once

#include "ArgumentType.hpp"
#include <string>

namespace args_parse {
	
	/**
	* @brief Базовый абстрактный класс для всех аргументов
	*/
	class Arg {
	protected:
		ArgumentType type;

		char option;
		const std::string longOption;
		const std::string description;
		std::string_view operands;
		bool isDefined = false;

		bool ParseOption(std::string_view arg);
		bool ParseLongOption(std::string_view arg);
	public:
		Arg(const char option, const std::string longOption, std::string description = "");
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