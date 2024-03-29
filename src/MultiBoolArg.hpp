#pragma once

#include "Arg.hpp"
#include <vector>

namespace args_parse {
	/**
	* @brief Класс мультибулевого аргумента
	* Аргумент содержит опцию и набор булевых операндов
	*/

	class MultiBoolArg : public Arg {
	private:
		std::vector<bool> values;
	public:
		MultiBoolArg(const char option, const char* longOption, const char* description = "");
		std::vector<bool> GetValues();
		bool Parse(std::string_view option) override;
		bool ParseLong(std::string_view option) override;
	};

}