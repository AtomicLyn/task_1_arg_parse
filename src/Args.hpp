#pragma once

#include "ParseResult.hpp"
#include "Validators.hpp"
#include "Helpers.hpp"
#include "UserTypes.hpp"

namespace args_parse {
	// Отладочный класс для доступа к приватным членам AbstractArg
	namespace args_parse_testing {
		class ArgsTestingAcessor;
	}
	/**
	* @brief Класс-перечисление основных типов аргументов
	* Используется для сопоставления типов при парсинге нескольких последовательных EmptyArg и определения последнего типа подпоследовательности
	*/
	enum class ArgumentType { Empty, NotEmpty };
	/**
	* @brief Базовый абстрактный класс для всех аргументов
	* Частично реализует общий функционал всех дочерних классов
	*/
	class AbstractArg {
		friend class args_parse_testing::ArgsTestingAcessor;
		friend class ArgParser;

		const char option; ///< Указывает короткое название аргумента
		const std::string longOption; ///< Указывает полное название аргумента
		const std::string description; ///< Указывает подробное описание аргумента
		const ArgumentType type; ///< Указывает, каким типом является объект

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
		[[nodiscard]] virtual ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) = 0;
		/**
		* @brief Чистый виртуальный метод полного парсинга длинной опции аргумента
		* Выполняет парсинг полного названия аргумента, после чего определяет значение из operands, соответствующее типу аргумента
		* @param[in] nextArg Следующий аргумент если таковой имеется
		* @param[in] usedNextArg Ссылка на булево значение, показывающее, был ли использован следующий аргумент
		*/
		[[nodiscard]] virtual ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) = 0;
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
		/**
		* @brief Метод предварительного парсинга опции аргумента
		* Выполняет парсинг короткого названия аргумента и сохраняет остраток строки в operands
		* @param[in] argWithoutDash входной аргумент из строки
		*/
	public:
		AbstractArg(ArgumentType type, const char option, const std::string longOption, std::string description = "");
		virtual ~AbstractArg();
		/// Геттер для option
		[[nodiscard]] const char GetOption() const;
		/// Геттер для longOption
		[[nodiscard]] std::string_view GetLongOption() const;
		/// Геттер для description
		[[nodiscard]] std::string_view GetDescription() const;
		/// Геттер для type
		[[nodiscard]] const ArgumentType GetType() const;
		/// Геттер для isDefined
		[[nodiscard]] const bool IsDefined() const;
	};


	/**
	* @brief Класс пустого аргумента
	* Аргумент не содержит ничего, кроме опции
	*/
	class EmptyArg : public AbstractArg {
		ParseResult ParseOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
		ParseResult ParseLongOperandAndSetDefined(std::optional<std::string> nextArg, bool& usedNextArg) override;
	public:
		EmptyArg(const char option, std::string longOption, std::string description = "");
	};

	/**
	* @brief Шаблон класса одиночного аргумента
	* Аргумент содержит опцию и шаблонный операнд
	*/
	template<typename T>
	class SingleArg : public AbstractArg {
		std::optional<std::reference_wrapper<Validator<T>>> validator; ///< Поле, хранящее валидатор для шаблонного типа
		T value; ///< Поле, хранящее значение аргумента в случае успешного парсинга

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;
			if (auto result = ParseType(value, operands); !result.IsOk()) return result;
			if (validator.has_value())
				if (const auto valResult = validator.value().get().Check(value); !valResult.IsOk()) return valResult;

			isDefined = true;

			return ParseResult::Ok();
		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;
			if (auto result = ParseType(value, operands); !result.IsOk()) return result;
			if (validator.has_value())
				if (const auto valResult = validator.value().get().Check(value); !valResult.IsOk()) return valResult;

			isDefined = true;

			return ParseResult::Ok();
		}
	public:
		SingleArg(const char option, std::string longOption, std::string description = "")
			: value{}, AbstractArg{ ArgumentType::NotEmpty, option, std::move(longOption), std::move(description) } {};

		SingleArg(std::reference_wrapper<Validator<T>> vvalidator, const char option, std::string longOption, std::string description = "")
			: SingleArg{ option, std::move(longOption), std::move(description) } {
			validator = vvalidator;
		};

		/// Геттер для value
		const T& GetValue() const {
			return value;
		}
	};

	/**
	* @brief Шаблон класса мультибулевого аргумента
	* Аргумент содержит опцию и набор булевых операндов
	*/
	template<typename T>
	class MultiArg : public AbstractArg {
		std::optional<std::reference_wrapper<Validator<T>>> validator;
		/// Поле, хранящее значения аргумента в случае успешного парсинга 
		/// @attention Может быть передано несколько одинаковых аргументов командной строки
		std::vector<T> values;

		ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			T value;

			if (auto result = ParseType(value, operands); !result.IsOk()) return result;
			if (validator.has_value())
				if (const auto valResult = validator.value().get().Check(value); !valResult.IsOk()) return valResult;

			values.push_back(value);

			isDefined = true;

			return ParseResult::Ok();
		}

		ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) override {
			if (auto result = CheckLongOperand(nextArg, usedNextArg); !result.IsOk()) return result;

			T value;

			if (auto result = ParseType(value, operands); !result.IsOk()) return result;
			if (validator.has_value())
				if (const auto valResult = validator.value().get().Check(value); !valResult.IsOk()) return valResult;

			values.push_back(value);

			isDefined = true;

			return ParseResult::Ok();
		}
	public:
		MultiArg(const char option, std::string longOption, std::string description = "")
			: AbstractArg(ArgumentType::NotEmpty, option, std::move(longOption), std::move(description)) {};

		MultiArg(std::reference_wrapper <Validator<T>> vvalidator, const char option, std::string longOption, std::string description = "")
			: AbstractArg(ArgumentType::NotEmpty, option, std::move(longOption), std::move(description)) {
			validator = vvalidator;
		};

		/// Геттер для values
		const std::vector<T>& GetValues() const {
			return values;
		}

		/// Количество значений в values
		auto GetCount() const {
			return values.size();
		}
	};

	namespace args_parse_testing {

		class ArgsTestingAcessor {
			AbstractArg& arg;
		public:
			ArgsTestingAcessor(AbstractArg& arg) : arg{ arg } {};
			ParseResult ParseOption(std::string_view argWithoutDash) {
				return arg.ParseOption(argWithoutDash);
			}
			std::pair<ParseResult, int> ParseLongOption(std::string_view argWithoutDash) {
				return arg.ParseLongOption(argWithoutDash);
			}
			ParseResult ParseOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
				return arg.ParseOperandAndSetDefined(nextArg, usedNextArg);
			}
			ParseResult ParseLongOperandAndSetDefined(const std::optional<std::string> nextArg, bool& usedNextArg) {
				return arg.ParseLongOperandAndSetDefined(nextArg, usedNextArg);
			}
		};

	}
}