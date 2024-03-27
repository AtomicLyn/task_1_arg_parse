#pragma once

#include "ArgumentType.hpp"

namespace args_parse {
	
	/**
	* @brief Базовый абстрактный класс для всех аргументов
	*/
	class Arg {
	protected:
		ArgumentType type;

		char option;
		const char* longOption;
		const char* description;
		const char* operands = "";
		bool isDefined = false;

		bool ParseOption(const char* arg);
		bool ParseLongOption(const char* arg);
	public:
		Arg(const char option, const char* longOption, const char* description = "");
		virtual ~Arg();
		char GetOption();
		const char* GetLongOption();
		const char* GetDescription();
		ArgumentType GetType();
		bool IsDefined();
		virtual bool Parse(const char* arg) = 0;
		virtual bool ParseLong(const char* arg) = 0;
		
	};

}