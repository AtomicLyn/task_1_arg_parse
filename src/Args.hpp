#pragma once

#include "ParseResult.hpp"
#include "Validators.hpp"
#include "Helpers.hpp"
#include "UserTypes.hpp"

namespace args_parse {
	/**
	* @brief Класс-перечисление основных типов аргументов
	* Используется для сопоставления типов при парсинге нескольких последовательных EmptyArg и определения последнего типа подпоследовательности
	*/
	enum class ArgumentType { UserType, Empty, Bool, Int, String, MultiBool, MultiInt, MultiString };
	/**
	* @brief Базовый абстрактный класс для всех аргументов
	* Частично реализует общий функционал всех дочерних классов
	*/
	class AbstractArg {
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
		AbstractArg(ArgumentType type, const char option, const std::string longOption, std::string description = "");
		virtual ~AbstractArg();
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
	class EmptyArg : public AbstractArg {
	public:
		EmptyArg(const char option, std::string longOption, std::string description = "");
		ParseResult ParseOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
	};

	/**
	* @brief Шаблон класса одиночного аргумента
	* Аргумент содержит опцию и шаблонный операнд
	*/
	template<typename T>
	class SingleArg : public AbstractArg {
		T value; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		SingleArg(const char option, std::string longOption, std::string description = "")
			: AbstractArg(ArgumentType::UserType, option, longOption, description) {};

		/// Геттер для value
		const T& GetValue() const {
			return value;
		}

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
			if (auto result = ParseUserType(value, operands); !result.IsOk()) return result;

			isDefined = true;

			return ParseResult::Ok();
		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
			if (auto result = ParseUserType(value, operands); !result.IsOk()) return result;

			isDefined = true;

			return ParseResult::Ok();
		}
	};

	/**
	* @brief Шаблонный класс булевого аргумента
	* Аргумент содержит опцию и булевый операнд
	*/
	template<>
	class SingleArg<bool> : public AbstractArg {
		const BoolValidator validator; //< Поле, хранящее валидатор значений аргумента
		bool value = false; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		SingleArg(const char option, std::string longOption, std::string description = "")
			: AbstractArg(ArgumentType::Bool, option, longOption, description) {};

		bool GetValue() const {
			return value;
		}

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsInteger(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

			const auto num = std::stoi(operands);

			if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

			value = num == 1;
			isDefined = true;

			return ParseResult::Ok();
		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsInteger(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

			const auto num = std::stoi(operands);

			if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

			value = num == 1;
			isDefined = true;

			return ParseResult::Ok();
		}
	};


	/**
	* @brief Шаблонный класс целочисленного аргумента
	* Аргумент содержит опцию и целочисленный операнд
	*/
	template<>
	class SingleArg<int> : public AbstractArg {
		std::unique_ptr<Validator<int>> validator; //< Поле, хранящее валидатор значений аргумента
		int value = -1; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		SingleArg(std::unique_ptr<Validator<int>> validator, const char option, std::string longOption, std::string description = "")
			: validator{ std::move(validator) }, AbstractArg(ArgumentType::Int, option, longOption, description) {};

		int GetValue() const {
			return value;
		}

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsInteger(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

			const auto num = std::stoi(operands);

			if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

			value = num;
			isDefined = true;

			return ParseResult::Ok();
		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsInteger(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

			const auto num = std::stoi(operands);

			if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

			value = num;
			isDefined = true;

			return ParseResult::Ok();
		}
	};


	/**
	* @brief Шаблонный класс вещественного аргумента
	* Аргумент содержит опцию и вещественнй операнд
	*/
	template<>
	class SingleArg<float> : public AbstractArg {
		std::unique_ptr<Validator<float>> validator; //< Поле, хранящее валидатор значений аргумента
		float value = -1; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		SingleArg(std::unique_ptr<Validator<float>> validator, const char option, std::string longOption, std::string description = "")
			: validator{ std::move(validator) }, AbstractArg(ArgumentType::Int, option, longOption, description) {};

		float GetValue() const {
			return value;
		}

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsFloat(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not float" });

			const auto num = std::stof(operands);

			if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

			value = num;
			isDefined = true;

			return ParseResult::Ok();
		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsFloat(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not float" });

			const auto num = std::stof(operands);

			if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

			value = num;
			isDefined = true;

			return ParseResult::Ok();
		}
	};


	/**
	* @brief Шаблонный класс строкового аргумента
	* Аргумент содержит опцию и строковый операнд
	*/
	template<>
	class SingleArg<std::string> : public AbstractArg {
		std::unique_ptr<Validator<std::string>> validator; //< Поле, хранящее валидатор значений аргумента
		std::string value; ///< Поле, хранящее значение аргумента в случае успешного парсинга
	public:
		SingleArg(std::unique_ptr<Validator<std::string>> validator, const char option, std::string longOption, std::string description = "")
			: validator{ std::move(validator) }, AbstractArg(ArgumentType::String, option, longOption, description) {};

		std::string_view GetValue() const {
			return value;
		}

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
			if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

			value = operands;
			isDefined = true;

			return ParseResult::Ok();
		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
			if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

			value = operands;
			isDefined = true;

			return ParseResult::Ok();
		}
	};

	/**
	* @brief Шаблон класса мультибулевого аргумента
	* Аргумент содержит опцию и набор булевых операндов
	*/
	template<typename T>
	class MultiArg : public AbstractArg {
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<T> values;
	public:
		MultiArg(const char option, std::string longOption, std::string description = "")
			: AbstractArg(ArgumentType::UserType, option, longOption, description) {};

		/// Геттер для values
		const std::vector<T>& GetValues() const {
			return values;
		}

		/// Количество значений в values
		int GetCount() const {
			return values.size();
		}

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			T value;

			if (auto result = ParseUserType(value, operands); !result.IsOk()) return result;

			values.push_back(value);

			isDefined = true;

			return ParseResult::Ok();
		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			T value;

			if (auto result = ParseUserType(value, operands); !result.IsOk()) return result;

			values.push_back(value);

			isDefined = true;

			return ParseResult::Ok();
		}
	};

	/**
	* @brief Шаблонный класс мультибулевого аргумента
	* Аргумент содержит опцию и набор булевых операндов
	*/
	template<>
	class MultiArg<bool> : public AbstractArg {
		const BoolValidator validator; //< Поле, хранящее валидатор значений аргумента
		std::vector<bool> values;
	public:
		MultiArg(const char option, std::string longOption, std::string description = "")
			: AbstractArg(ArgumentType::MultiBool, option, longOption, description) {};

		const std::vector<bool>& GetValues() const {
			return values;
		}

		int GetCount() const {
			return values.size();
		}

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsInteger(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

			const auto num = std::stoi(operands);

			if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

			values.push_back(num == 1);
			isDefined = true;

			return ParseResult::Ok();

		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsInteger(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + " : The option is found, but the value is not integer" });

			const auto num = std::stoi(operands);

			if (const auto valResult = validator.Check(num); !valResult.IsOk()) return valResult;

			values.push_back(num == 1);
			isDefined = true;

			return ParseResult::Ok();
		}
	};


	/**
	* @brief Шаблонный класс мультицелочисленного аргумента
	* Аргумент содержит опцию и набор целочисленных операндов
	*/
	template<>
	class MultiArg<int> : public AbstractArg {
		const std::unique_ptr<Validator<int>> validator; //< Поле, хранящее валидатор значений аргумента
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<int> values;
	public:
		MultiArg(std::unique_ptr<Validator<int>> validator, const char option, std::string longOption, std::string description = "")
			: validator{ std::move(validator) }, AbstractArg(ArgumentType::MultiInt, option, longOption, description) {};

		const std::vector<int>& GetValues() const {
			return values;
		}

		int GetCount() const {
			return values.size();
		}

		ParseResult ParseOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsInteger(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + ": The option is found, but the value is not integer" });

			auto num = std::stoi(operands);

			if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

			values.push_back(num);
			isDefined = true;

			return ParseResult::Ok();
		}
		ParseResult ParseLongOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsInteger(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + ": The option is found, but the value is not integer" });

			auto num = std::stoi(operands);

			if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

			values.push_back(num);
			isDefined = true;

			return ParseResult::Ok();
		}
	};


	/**
	* @brief Шаблонный класс мультивещественного аргумента
	* Аргумент содержит опцию и набор вещественных операндов
	*/
	template<>
	class MultiArg<float> : public AbstractArg {
		const std::unique_ptr<Validator<float>> validator; //< Поле, хранящее валидатор значений аргумента
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<float> values;
	public:
		MultiArg(std::unique_ptr<Validator<float>> validator, const char option, std::string longOption, std::string description = "")
			: validator{ std::move(validator) }, AbstractArg(ArgumentType::MultiInt, option, longOption, description) {};

		const std::vector<float>& GetValues() const {
			return values;
		}

		int GetCount() const {
			return values.size();
		}

		ParseResult ParseOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsFloat(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + ": The option is found, but the value is not float" });

			auto num = std::stof(operands);

			if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

			values.push_back(num);
			isDefined = true;

			return ParseResult::Ok();
		}
		ParseResult ParseLongOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			if (!IsFloat(operands))
				return ParseResult::Fail({ "In " + currentArg + " " + (nextArg.has_value() ? nextArg.value() : "") + ": The option is found, but the value is not float" });

			auto num = std::stof(operands);

			if (const auto valResult = validator->Check(num); !valResult.IsOk()) return valResult;

			values.push_back(num);
			isDefined = true;

			return ParseResult::Ok();
		}
	};


	/**
	* @brief Класс мультистрокового аргумента
	* Аргумент содержит опцию и набор строковых операндов
	*/
	template<>
	class MultiArg<std::string> : public AbstractArg {
		const std::unique_ptr<Validator<std::string>> validator; //< Поле, хранящее валидатор значений аргумента
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @warning Может быть передано несколько одинаковых аргументов командной строки
		std::vector<std::string> values;
	public:
		MultiArg(std::unique_ptr<Validator<std::string>> validator, const char option, std::string longOption, std::string description = "")
			: validator{ std::move(validator) }, AbstractArg(ArgumentType::MultiString, option, longOption, description) {};

		const std::vector<std::string>& GetValues() const {
			return values;
		}

		int GetCount() const {
			return values.size();
		}

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
			if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

			values.push_back(operands);
			isDefined = true;

			return ParseResult::Ok();
		}
		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
			if (const auto valResult = validator->Check(operands); !valResult.IsOk()) return valResult;

			values.push_back(operands);
			isDefined = true;

			return ParseResult::Ok();
		}
	};
}