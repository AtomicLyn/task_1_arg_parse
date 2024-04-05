#pragma once
#include <string>
#include <optional>

namespace args_parse {

	/// @brief Структура для хранения сообщения о неудачном парсинге
	struct Error {
		std::string Message; ///< Сообщение об ошибке
	};

	class [[nodiscard]] ParseResult {
		std::optional<Error> error; ///< Опциональное поле, хранящее ошибку в случае ошибки парсинга

		ParseResult() = default;
		ParseResult(Error err) : error{ std::move(err) } {};

	public:
		static ParseResult Ok() { return ParseResult{}; }


		static ParseResult Fail() { return ParseResult{ {  } }; } ///< В случае, если аргумент не был найден
		static ParseResult Fail(Error err) { return ParseResult{ err }; }

		[[nodiscard]] const bool IsOk() const { return !error.has_value(); } ///< Метод для определения результата парсинга
		/// Метод для определения, найден ли был аргумент во время парсинга
		[[nodiscard]] const bool IsNotFound() const { return error.has_value() ? error.value().Message.empty() : false; }
		[[nodiscard]] const Error& GetError() const { return error.value(); } ///< Геттер для Error, если результат содержал ошибку
	};

}