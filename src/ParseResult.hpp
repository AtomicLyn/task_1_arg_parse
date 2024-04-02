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
		static ParseResult Fail() { return ParseResult{ { } }; } ///< В случае, если аргумент не был найден
		static ParseResult Fail(Error err) { return ParseResult{ err }; }

		/// @brief Метод для определения результата парсинга
		[[nodiscard]] const bool IsOk() const { return !error.has_value(); }
		[[nodiscard]] const Error& GetError() const { return error.value(); } ///< Геттер для Error, если результат содержал ошибку
	};

}