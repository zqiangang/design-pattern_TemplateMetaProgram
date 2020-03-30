#ifndef _ABSTRACT_FACTORY_HPP_
#define _ABSTRACT_FACTORY_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *		* ʹ�ü�� *
 *		* step.1 *
 *	���ȴ����Լ��� class ����(��������)�������, �ο� abstract_factory_example step.1
 *		* step.2 *
 *	�����Լ��ĳ������
 *	�ο�ʹ�� abstract_factory_example 
 *		* step.3 *
 * ʹ�ø�ģʽ, �ο�ʹ�� abstract_factory_example 
 */

/*
 *  ���󹤳�ģʽ
 *  ע��     :  minin_types ��Ӧ��ȫΪ��,�Ҿ�Ϊ class ����,���ٴ���һ�� ģ���β��� abstract ��.
 *  ģ���β� :  minix_types ����ĳ��󷽷�
 */
template <typename ... minix_types>
class _abstract_factory_pattern_impl : public sequence_minixs_inherit<minix_types...>
{
private:
	static_assert(std::conjunction_v<std::is_class<minix_types>...>, "all element type of minix_types ,must be is class type");
	static_assert(!std::conjunction_v<std::is_empty<minix_types>...>, "all element type of minix_types is empty class");
	static_assert(std::disjunction_v<std::is_polymorphic<minix_types> ...>, "factory inherit all class element of minix_types,the result class must be polymorphic");
public:
    using result_type = _abstract_factory_pattern_impl<minix_types...>;
};

template <typename minix_type>
class _abstract_factory_pattern_impl<minix_type> : public minix_type
{
private:
    static_assert(std::is_class_v<minix_type>, "minix_types must be is class type");
    static_assert(!std::is_empty_v<minix_type>, "minix_type should not is empty class");
    static_assert(std::is_polymorphic_v<minix_type>, "minix_type class must be polymorphic");
public:
    using result_type = std::conditional_t<std::is_abstract_v<minix_type>, _abstract_factory_pattern_impl<minix_type>, minix_type>;
};

template <typename ... minix_types>
using abstract_factory_pattern_impl = typename _abstract_factory_pattern_impl<minix_types...>::result_type;

DESIGN_PATTERN_END
#endif // !_ABSTRACT_FACTORY_HPP_
