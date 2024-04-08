#pragma once

#include "Args.hpp"

namespace args_parse {
	/**
	* @brief Класс парсера аргументов командной строки
	* Используется для проведения парсинга аргументов командной строки из возможных аргументов arguments
	* прим.
	* @code
	* -a
	* -a 10
	* -a=10
	* --authorize 10
	* --authorize=10
	* -abc
	* -abc=10
	* -abc10
	* -abc 10
	* --authorize=10 --authority=10
	* --authoriz=10 --authorit=10
	* @endcode
	*/
	class ArgParser {
		std::vector<Arg*> arguments; ///< Поле, хранящее возможные аргументы в командной строке
		/**
		* @brief Вспомогательный метод для парсинга последовательности нескольких аргументов
		* Метод выполняет парсинг подпоследовательности после первого встретившегося аргумента. Определяет последовательность пустых аргументов и любой возможный аргумент на конце
		*/
		[[nodiscard]] ParseResult ParseSubsequence(std::string_view argumentWithoutDash, std::optional<std::string> nextArg, bool& usedNextArg);
	public:
		/// Метод для добавления возможного аргумента командной строки
		void Add(Arg* argument);
		/**
		* @brief Основной метод парсинга аргументов командной строки
		* Выполняет последовательный парсинг каждого принятого аргумента из командной строки.
		* По умолчанию все аргументы командной строки являются не обязательными.
		* @return True , если парсинг всех аргументов из возможных arguments выполнен успешного
		* @return False , если во время парсинга одного из аргументов возникла ошибка
		*/
		[[nodiscard]] ParseResult Parse(const int argc, const char** argv);
		/// Метод для получения всей доступной информации о возможных аргументах
		const std::string GetHelp() const;
	};
}
