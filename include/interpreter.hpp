#ifndef _INTERPRETER_HPP_
#define _INTERPRETER_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *  解释器模式
 *	模板形参们 : minix_types , 用户需要的方法和数据成员
 *  断言约束 : 要求混入类都必须时 class 类型
 *  宏 : 如果ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC定义，那么检查是否为多态
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
