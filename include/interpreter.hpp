#ifndef _INTERPRETER_HPP_
#define _INTERPRETER_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *  ������ģʽ
 *	ģ���β��� : minix_types , �û���Ҫ�ķ��������ݳ�Ա
 *  ����Լ�� : Ҫ������඼����ʱ class ����
 *  �� : ���ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC���壬��ô����Ƿ�Ϊ��̬
*/
template <typename ... minix_types>
class interpreter_patterm_impl :
	public sequence_minixs_inherit<minix_types...>
{
	static_assert(std::conjunction_v<std::is_class<minix_types>...>, "all elements type of minix_types should be class type");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
    static_assert(std::disjunction_v<std::is_polymorphic<minix_types>...>, "interpreter should be an  polymorphic class type");
#endif
};

DESIGN_PATTERN_END
#endif // !_INTERPRETER_HPP_
