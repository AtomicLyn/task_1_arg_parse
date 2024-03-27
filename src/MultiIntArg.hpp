#pragma once

#include "Arg.hpp"
#include <vector>

namespace args_parse {
	/**
	* @brief ����� �������������������� ���������
	* �������� �������� ����� � ����� ������������� ���������
	*/
	class MultiIntArg : public Arg {
	private:
		std::vector<int> values;
	public:
		MultiIntArg(const char option, const char* longOption, const char* description = "");
		std::vector<int> GetValues();
		bool Parse(const char* arg) override;
		bool ParseLong(const char* arg) override;
	};

}