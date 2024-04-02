#pragma once

#include "ArgumentType.hpp"
#include "Result.hpp"
#include <string>
#include <string_view>

namespace args_parse {
	
	/**
	* @brief Базовый абстрактный класс для всех аргументов
	* Частично реализует общий функционал всех дочерних классов
	*/
	class Arg {
		const ArgumentType type; ///< Указывает, каким типом является объект
		char option; ///< Указывает короткое название аргумента
		const std::string longOption; ///< Указывает полное название аргумента
		const std::string description; ///< Указывает подробное описание аргумента

	protected:
		std::string operands; ///< Хранит остаток строки после предварительного парсинга
		bool isDefined = false; ///< Указывает, был ли успешно найден аргумент в процессе парсинга

		/** 
		* @brief Метод предварительного парсинга опции аргумента
		* Выполняет парсинг короткого названия аргумента и сохраняет остраток строки в operands
		* @param[in] argWithoutDash входной аргумент из строки
		*/ 
		[[nodiscard]] const bool ParseOption(std::string_view argWithoutDash);
		/**
		* @brief Метод предварительного парсинга длинной опции аргумента
		* Выполняет парсинг полного названия аргумента и сохраняет остраток строки в operands
		* @param[in] argWithoutDash входной аргумент из строки
		*/
		[[nodiscard]] const bool ParseLongOption(std::string_view argWithoutDash);
	public:
		Arg(ArgumentType type, const char option, const std::string longOption,  std::string description = "");
		virtual ~Arg();
		const char GetOption() const; ///< Геттер для option
		const std::string GetLongOption() const; ///< Геттер для longOption
		const std::string GetDescription() const; ///< Геттер для description
		[[nodiscard]] const ArgumentType GetType() const; ///< Геттер для type
		[[nodiscard]] const bool IsDefined() const; ///< Геттер для isDefined
		/**
		* @brief Чистый виртуальный метод полного парсинга опции аргумента
		* Выполняет парсинг короткого названия аргумента, после чего определяет значение из operands, соответствующее типу аргумента
		* @param[in] arg входной аргумент из строки
		*/
		[[nodiscard]] virtual const bool Parse(std::string_view arg) = 0;
		/**
		* @brief Чистый виртуальный метод полного парсинга длинной опции аргумента
		* Выполняет парсинг полного названия аргумента, после чего определяет значение из operands, соответствующее типу аргумента
		* @param[in] arg входной аргумент из строки
		*/
		[[nodiscard]] virtual const bool ParseLong(std::string_view arg) = 0;
		
	};

}