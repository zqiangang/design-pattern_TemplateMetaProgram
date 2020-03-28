#ifndef _FACADE_HPP_
#define _FACADE_HPP_
#include "dp_tool_kits.hpp"
#include "singleton.hpp"
DESIGN_PATTERN_START

/*
 *  作用 : 处理当需要有多个 facade_objects 时
 *       : 形如 facade_pattern_impl<facade_box<Facade_Objects...>>
 */
template <typename ... minix_objects>
class facade_box : public sequence_minixs_inherit<minix_objects...>
{};

/* 
 *  门面模式
 *  模板形参 : facade_object, 已经实现或声明的门面对象或抽象接口
 *			 : stat , 决定是否使用,单例模式在当前的 facade 中
 *  断言约束 : facade_object 应当不为空且应当是一个 class 类型
 *  成员类型 : result_type 返回的组合的结果类型
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
 *  门面模式别名
 */
template <typename facade_object, bool stat = true>
using facade_pattern_impl = typename _facade_pattern_impl<facade_object, stat>::result_type;

DESIGN_PATTERN_END
#endif // !_FACADE_HPP_


