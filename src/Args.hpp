#pragma once

#include "ParseResult.hpp"
#include "Validators.hpp"

namespace args_parse {
	/**
	* @brief Класс-перечисление основных типов аргументов
	* Используется для сопоставления типов при парсинге нескольких последовательных EmptyArg и определения последнего типа подпоследовательности
	*/
	enum class ArgumentType { Empty, Bool, Int, String, MultiBool, MultiInt, MultiString };
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
	
		/// Метод проверки операндов короткого аргумента и сдвига operands
		/// @param[in] nextArg Следующий аргумент если таковой имеется
		/// @param[in] usedNextArg Ссылка на булево значение, показывающее, был ли использован следующий аргумент
		[[nodiscard]] ParseResult CheckOperand(std::optional<std::string> nextArg, bool& usedNextArg);
		/// Метод проверки операндов длинного аргумента и сдвига operands
		/// @param[in] usedNextArg Ссылка на булево значение, показывающее, был ли использован следующий аргумент
		[[nodiscard]] ParseResult CheckLongOperand(std::optional<std::string> nextArg, bool& usedNextArg);
	public:
		Arg(ArgumentType type, const char option, const std::string longOption,  std::string description = "");
		virtual ~Arg();
		/// Геттер для option
		const char GetOption() const; 
		/// Геттер для longOption
		std::string_view GetLongOption() const; 
		/// Геттер для description
		std::string_view GetDescription() const;
		/// Геттер для type
		[[nodiscard]] const ArgumentType GetType() const; 
		/// Геттер для isDefined
		[[nodiscard]] const bool IsDefined() const;	
		/**
		* @brief Метод предварительного парсинга опции аргумента
		* Выполняет парсинг короткого названия аргумента и сохраняет остраток строки в operands
		* @param[in] argWithoutDash входной аргумент из строки
		*/
		[[nodiscard]] ParseResult ParseOption(std::string_view argWithoutDash);
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
		* @param[in] nextArg Следующий аргумент если таковой имеется
		* @param[in] usedNextArg Ссылка на булево значение, показывающее, был ли использован следующий аргумент
		*/
		[[nodiscard]] virtual ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nexArg, bool& usedNextArg) = 0;
		/**
		* @brief Чистый виртуальный метод полного парсинга длинной опции аргумента
		* Выполняет парсинг полного названия аргумента, после чего определяет значение из operands, соответствующее типу аргумента
		* @param[in] nextArg Следующий аргумент если таковой имеется
		* @param[in] usedNextArg Ссылка на булево значение, показывающее, был ли использован следующий аргумент
		*/
		[[nodiscard]] virtual ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nexArg, bool& usedNextArg) = 0;
		
	};


	/**
	* @brief Класс пустого аргумента
	* Аргумент не содержит ничего, кроме опции
	*/
	class EmptyArg : public Arg {
	public:
		EmptyArg(const char option, std::string longOption, std::string description = "");
		ParseResult ParseOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
	};


	/**
	* @brief Класс булевого аргумента
	* Аргумент содержит опцию и булевый операнд
	*/
	class BoolArg : public Arg {
		const BoolValidator validator;
		bool value = false; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		BoolArg(const char option, std::string longOption, std::string description = "");
		/// Геттер для value
		const bool GetValue() const;
		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};


	/**
	* @brief Класс целочисленного аргумента
	* Аргумент содержит опцию и целочисленный операнд
	*/
	class IntArg : public Arg {
		std::unique_ptr<Validator<int>> validator;
		int value = -1; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		IntArg(std::unique_ptr<Validator<int>> validator, const char option, std::string longOption, std::string description = "");
		/// Геттер для value
		const int GetValue() const;
		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};


	/**
	* @brief Класс строкового аргумента
	* Аргумент содержит опцию и строковый операнд
	*/
	class StringArg : public Arg {
		std::unique_ptr<Validator<std::string>> validator;
		std::string value; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		StringArg(std::unique_ptr<Validator<std::string>> validator, const char option, std::string longOption, std::string description = "");
		/// Геттер для value
		std::string_view GetValue() const;
		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};


	/**
	* @brief Класс мультибулевого аргумента
	* Аргумент содержит опцию и набор булевых операндов
	*/
	class MultiBoolArg : public Arg {
		const BoolValidator validator;
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<bool> values;
	public:
		MultiBoolArg(const char option, std::string longOption, std::string description = "");
		/// Геттер для values
		const std::vector<bool>& GetValues() const;
		/// Количество значений в values
		const int GetCount() const;
		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};


	/**
	* @brief Класс мультицелочисленного аргумента
	* Аргумент содержит опцию и набор целочисленных операндов
	*/
	class MultiIntArg : public Arg {
		const std::unique_ptr<Validator<int>> validator;
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<int> values;
	public:
		MultiIntArg(std::unique_ptr<Validator<int>> validator, const char option, std::string longOption, std::string description = "");
		/// Геттер для values
		const std::vector<int>& GetValues() const;
		/// Количество значений в values
		const int GetCount() const;
		ParseResult ParseOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
	};


	/**
	* @brief Класс мультистрокового аргумента
	* Аргумент содержит опцию и набор строковых операндов
	*/
	class MultiStringArg : public Arg {
		const std::unique_ptr<Validator<std::string>> validator;
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<std::string> values;
	public:
		MultiStringArg(std::unique_ptr<Validator<std::string>> validator, const char option, std::string longOption, std::string description = "");
		/// Геттер для values
		const std::vector<std::string>& GetValues() const;
		/// Количество значений в values
		const int GetCount() const;
		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override;
	};
}