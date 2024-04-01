#pragma once

namespace args_parse {
	/**
	* @brief Класс-перечисление основных типов аргументов
	* Используется для сопоставления типов при парсинге нескольких последовательных EmptyArg и определения последнего типа последовательности
	*/

	enum class ArgumentType { Empty, Bool, Int, String, MultiBool, MultiInt, MultiString };
}