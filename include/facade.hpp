#ifndef _FACADE_HPP_
#define _FACADE_HPP_
#include "dp_tool_kits.hpp"
#include "singleton.hpp"
DESIGN_PATTERN_START

/*
 *  ���� : ������Ҫ�ж�� facade_objects ʱ
 *       : ���� facade_pattern_impl<facade_box<Facade_Objects...>>
 */
template <typename ... minix_objects>
class facade_box : public sequence_minixs_inherit<minix_objects...>
{};

/* 
 *  ����ģʽ
 *  ģ���β� : facade_object, �Ѿ�ʵ�ֻ������������������ӿ�
 *			 : stat , �����Ƿ�ʹ��,����ģʽ�ڵ�ǰ�� facade ��
 *  ����Լ�� : facade_object Ӧ����Ϊ����Ӧ����һ�� class ����
 *  ��Ա���� : result_type ���ص���ϵĽ������
 */
template <typename facade_object, bool stat>
class _facade_pattern_impl : public _facade_pattern_impl<facade_object, stat>
{
	static_assert(std::is_class_v<facade_object>, "facade object must be an class type");
	static_assert(std::is_empty_v<facade_object>, "facade object should not is empty class");
public:
	using result_type = std::conditional_t<stat, singleton_pattern_impl<facade_object>, facade_object>;
};

/*
 *  ����ģʽ����
 */
template <typename facade_object, bool stat = true>
using facade_pattern_impl = typename _facade_pattern_impl<facade_object, stat>::result_type;

DESIGN_PATTERN_END
#endif // !_FACADE_HPP_


