#ifndef _ABSTRACT_FACTORY_HPP_
#define _ABSTRACT_FACTORY_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *		* 使用简介 *
 *		* step.1 *
 *	首先创建自己的 class 混入(单个或多个)抽象基类, 参考 abstract_factory_example step.1
 *		* step.2 *
 *	创建自己的抽象基类
 *	参考使用 abstract_factory_example 
 *		* step.3 *
 * 使用该模式, 参考使用 abstract_factory_example 
 */

/*
 *  抽象工厂模式
 *  注意     :  minin_types 不应当全为空,且均为 class 类型,至少存在一个 模板形参是 abstract 的.
 *  模板形参 :  minix_types 混入的抽象方法
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
