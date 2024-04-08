#pragma once
#include <string>
#include <optional>

namespace args_parse {

	/// @brief Структура для хранения сообщения о неудачном парсинге
	struct Error {
		std::string Message; ///< Сообщение об ошибке
	};

	/// @brief Класс для хранения результата парсинга
	class [[nodiscard]] ParseResult {
		std::optional<Error> error; ///< Опциональное поле, хранящее ошибку в случае ошибки парсинга

		ParseResult() = default;
		ParseResult(Error err) : error{ std::move(err) } {};

	public:
		/// Фабричный метод для случая, если парсинг успешно выполнен
		[[nodiscard]] static ParseResult Ok() { return ParseResult{}; }
		/// Фабричный метод для случая, если аргумент не был найден
		[[nodiscard]] static ParseResult Fail() { return ParseResult{ {  } }; }
		/// Фабричный метод для случая, если парсинг завершился с ошибкой
		[[nodiscard]] static ParseResult Fail(Error err) { return ParseResult{ std::move(err) }; }

		/// Метод для определения результата парсинга
		[[nodiscard]] const bool IsOk() const { return !error.has_value(); } 
		/// Метод для определения, найден ли был аргумент во время парсинга
		[[nodiscard]] const bool IsNotFound() const { return error.has_value() ? error.value().Message.empty() : false; }
		/// Геттер для Error, если результат содержал ошибку
		[[nodiscard]] const Error& GetError() const { return error.value(); } 
	};

}