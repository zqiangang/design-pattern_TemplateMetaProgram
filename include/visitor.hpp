#ifndef _VISITOR_HPP_
#define _VISITOR_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *  访问者模式-访问者
 *  模板形参们 : 提供一些的访问者方法
 */
template <typename ... minix_types>
class visitor_visitor_pattern_impl :
	public sequence_minixs_inherit<minix_types...>
{};

/*
 *	作用 : 提供一些基本的方法
 *	模板形参 : visitor , 访问者类型
 */
template <typename visitor>
class default_visitor_hack_method
{
public:
	using visitor_type = visitor;
	virtual void accept(visitor_type*) = 0;
};

/*
 *	访问者模式-元素
 *	模板形参 : visitor , 访问者类型
 *  模板模板形参 : hack_method , 提供一些默认的方法
 *  模板模板形参们 : 提供一些用户自定义的方法和数据
 *  断言约束 : visitor 应当是一个 class 类型
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