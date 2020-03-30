#ifndef _VISITOR_HPP_
#define _VISITOR_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *  ������ģʽ-������
 *  ģ���β��� : �ṩһЩ�ķ����߷���
 */
template <typename ... minix_types>
class visitor_visitor_pattern_impl :
	public sequence_minixs_inherit<minix_types...>
{};

/*
 *	���� : �ṩһЩ�����ķ���
 *	ģ���β� : visitor , ����������
 */
template <typename visitor>
class default_visitor_hack_method
{
public:
	using visitor_type = visitor;
	virtual void accept(visitor_type*) = 0;
};

/*
 *	������ģʽ-Ԫ��
 *	ģ���β� : visitor , ����������
 *  ģ��ģ���β� : hack_method , �ṩһЩĬ�ϵķ���
 *  ģ��ģ���β��� : �ṩһЩ�û��Զ���ķ���������
 *  ����Լ�� : visitor Ӧ����һ�� class ����
 */
template <typename visitor,
	template <typename> class hack_method = default_visitor_hack_method,
	template <typename> class ... minix_types>
class visitor_element_pattern_impl :
	public hack_method<visitor>,
	public sequence_template_inherit<visitor_element_pattern_impl<visitor,hack_method,minix_types...>,minix_types...>
{
	static_assert(std::is_class_v<visitor>, "visitor should is an class type");
};

DESIGN_PATTERN_END
#endif