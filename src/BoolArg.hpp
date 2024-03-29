#pragma once

#include "Arg.hpp"

namespace args_parse {
	/**
	* @brief Класс булевого аргумента
	* Аргумент содержит опцию и булевый операнд
	*/

	class BoolArg : public Arg {
	private:
		bool value = false;
	public: 
		BoolArg(const char option, std::string longOption, std::string description = "");
		bool GetValue();
		bool Parse(std::string_view option) override;
		bool ParseLong(std::string_view option) override;
	};

}