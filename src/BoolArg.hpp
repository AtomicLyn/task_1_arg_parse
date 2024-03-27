#pragma once

#include "Arg.hpp"

namespace args_parse {
	/**
	* @brief ����� �������� ���������
	* �������� �������� ����� � ������� �������
	*/
	class BoolArg : public Arg {
	private:
		bool value = false;
	public: 
		BoolArg(const char option, const char* longOption, const char* description = "");
		bool GetValue();
		bool Parse(const char* option) override;
		bool ParseLong(const char* option) override;
	};

}