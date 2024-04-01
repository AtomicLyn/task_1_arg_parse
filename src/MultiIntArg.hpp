#pragma once

#include "Arg.hpp"
#include <vector>

namespace args_parse {
	/**
	* @brief Класс мультицелочисленного аргумента
	* Аргумент содержит опцию и набор целочисленных операндов
	*/

	class MultiIntArg : public Arg {
	private:
		std::vector<int> values;
	public:
		MultiIntArg(const char option, std::string longOption, std::string description = "");
		const std::vector<int> GetValues();
		const bool Parse(std::string_view arg) override;
		const bool ParseLong(std::string_view arg) override;
	};

}