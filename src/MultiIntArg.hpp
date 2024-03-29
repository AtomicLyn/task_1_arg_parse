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
		std::vector<int> GetValues();
		bool Parse(std::string_view arg) override;
		bool ParseLong(std::string_view arg) override;
	};

}