#ifndef _TEMPLATE_METHOD_HPP_
#define _TEMPLATE_METHOD_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	ģ�巽��ģʽ
 *	ģ��ģ���β� : master_template , ��Ҫ��ģ��,��ģ����Ե��� template_method_pattern_impl �� �����������
 *				 : public �� protected ������ master_template Ӧ���ṩģ�巽�������岿��
 *  ģ��ģ�巽���� : minix_types �� ����ܷ�������Ҫ��һЩ������������
 *  ��Ԫ���� : ȷ�� master_template ���Է�������������� public �� protected ����������
*/
template<template<typename> class master_template,
	template<typename> class ... minix_types>
class template_method_pattern_impl :
	public sequence_template_inherit<template_method_pattern_impl<master_template,minix_types...>,master_template, minix_types...>
{
	friend class master_template<template_method_pattern_impl<master_template, minix_types...>>;
};


DESIGN_PATTERN_END
#endif // !_TEMPLATE_METHOD_HPP_
