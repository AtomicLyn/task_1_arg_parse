#pragma once

namespace args_parse {
	/**
	* @brief �����-������������ �������� ����� ����������
	* ������������ ��� ������������� ����� ��� �������� ���������� ���������������� EmptyArg
	*/
	enum class ArgumentType { Empty, Bool, Int, String, MultiBool, MultiInt, MultiString };
}