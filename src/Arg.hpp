#pragma once

#include "ArgumentType.hpp"
#include "ParseResult.hpp"
#include <string>
#include <string_view>
#include <utility>

namespace args_parse {
	
	/**
	* @brief Базовый абстрактный класс для всех аргументов
	* Частично реализует общий функционал всех дочерних классов
	*/
	class Arg {
		const char option; ///< Указывает короткое название аргумента
		const std::string longOption; ///< Указывает полное название аргумента
		const std::string description; ///< Указывает подробное описание аргумента
		const ArgumentType type; ///< Указывает, каким типом является объект

	protected:		
		std::string currentArg; ///< Текущая полученная для парсинга строка
		std::string operands; ///< Хранит остаток строки после предварительного парсинга
		bool isDefined = false; ///< Указывает, был ли успешно найден аргумент в процессе парсинга
	
	public:
		Arg(ArgumentType type, const char option, const std::string longOption,  std::string description = "");
		virtual ~Arg();
		const char GetOption() const; ///< Геттер для option
		const std::string GetLongOption() const; ///< Геттер для longOption
		const std::string GetDescription() const; ///< Геттер для description
		[[nodiscard]] const ArgumentType GetType() const; ///< Геттер для type
		[[nodiscard]] const bool IsDefined() const; ///< Геттер для isDefined	
		/**
		* @brief Метод предварительного парсинга опции аргумента
		* Выполняет парсинг короткого названия аргумента и сохраняет остраток строки в operands
		* @param[in] argWithoutDash входной аргумент из строки
		*/
		[[nodiscard]] const ParseResult ParseOption(std::string_view argWithoutDash);
		/**
		* @brief Метод предварительного парсинга длинной опции аргумента
		* Выполняет парсинг полного названия аргумента и сохраняет остраток строки в operands
		* @param[in] argWithoutDash входной аргумент из строки
		* Возвращает пару значений с результатом парсинга и количеством совпавших символов в случае успешного парсинга
		*/
		[[nodiscard]] const std::pair<ParseResult, int> ParseLongOption(std::string_view argWithoutDash);
		
		/**
		* @brief Чистый виртуальный метод полного парсинга опции аргумента
		* Выполняет парсинг короткого названия аргумента, после чего определяет значение из operands, соответствующее типу аргумента
		* @param[in] arg входной аргумент из строки
		*/
		[[nodiscard]] virtual const ParseResult ParseOperandAndSetDefined() = 0;
		/**
		* @brief Чистый виртуальный метод полного парсинга длинной опции аргумента
		* Выполняет парсинг полного названия аргумента, после чего определяет значение из operands, соответствующее типу аргумента
		* @param[in] arg входной аргумент из строки
		*/
		[[nodiscard]] virtual const ParseResult ParseLongOperandAndSetDefined() = 0;
		
	};

}