#pragma once
#include <string>
#include <optional>

namespace args_parse {

	struct Error {
		std::string Message;
	};

	class [[nodiscard]] ParseResult {
		const std::optional<Error> error;

		ParseResult() = default;
		ParseResult(Error err) : error{ std::move(err) } {};

	public:
		static ParseResult Ok() { return ParseResult{}; }
		static ParseResult Fail(Error err) { return ParseResult{ err }; }

		[[nodiscard]] const bool IsOk() const { return error.has_value(); }
		[[nodiscard]] const Error& GetError() const { return error.value(); }
	};

}