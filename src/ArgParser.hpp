#pragma once

#include "Arg.hpp"
#include <vector>
#include <memory>

namespace args_parse {
	/**
	* @brief Класс парсера аргументов командной строки
	* Используется для проведения парсинга аргументов командной строки из возможных аргументов arguments
	*/
	class ArgParser {
		std::vector<std::unique_ptr<Arg*>> arguments; ///< Поле, хранящее возможные аргументы в командной строке
		/**
		* @brief Вспомогательный метод для парсинга последовательности нескольких аргументов
		* Метод выполняет парсинг подпоследовательности после первого встретившегося аргумента. Определяет последовательность пустых аргументов и любой возможный аргумент на конце
		* прим. 
		* @code 
		* -abc
		* -abc=10
		* -abc10
		* -abc 10
		* @endcode
		*/
		[[nodiscard]] const ParseResult ParseSubsequence(std::string_view argumentWithoutDash);
	public:
		void Add(Arg* argument); ///< Метод для добавления возможного аргумента командной строки
		/**
		* @brief Основной метод парсинга аргументов командной строки
		* Выполняет последовательный парсинг каждого принятого аргумента из командной строки.
		* По умолчанию все аргументы командной строки являются не обязательными.
		* @warning Возвращает True , если парсинг всех аргументов из возможных arguments выполнен успешного
		* @warning Возвращает False , если во время парсинга одного из аргументов возникла ошибка
		*/
		[[nodiscard]] const ParseResult Parse(const int argc, const char** argv);
		const std::string GetHelp() const; ///< Метод для получения всей доступной информации о возможных аргументах
	};
}
