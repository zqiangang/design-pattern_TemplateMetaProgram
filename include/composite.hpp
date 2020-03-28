#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	组合模式
 *  模板形参 : minix_types , 需要被混入的基类们,用于提供接口方法
 *  断言约束 : 所有的混入类,应当都是 class 类型
 *  宏       : 当 ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC 定义式,启用多态断言约束
 *  成员类型 : result_type 返回的组合的结果类型
 */
template <typename ... minix_types>
class _composite_pattern_impl : public sequence_minixs_inherit<minix_types...>
{
	static_assert(std::conjunction_v<std::is_class<minix_types>...>, "found element type of minix_type has an non class type");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::disjunction_v<std::is_polymorphic<minix_types>...>, "factory inherit all class element of minix_types,the result class must be polymorphic");
#endif
public:
	using result_type = _composite_pattern_impl<minix_types...>;
};

/*
 *  组合模式特化, 仅当有一个混入类时
 *  断言约束 : 混入类应当是 class 类型
 *  宏       : 当 ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC 定义式,启用多态断言约束
 *  成员类型 : result_type 返回的组合的结果类型
 */
template <typename minix_type>
class _composite_pattern_impl<minix_type> : public minix_type
{
	static_assert(std::is_class_v<minix_type>, "found element type of minix_type has an non class type");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::is_polymorphic_v<minix_type>, "factory inherit all class element of minix_types,the result class must be polymorphic");
#endif
public:
	using result_type = std::conditional_t<std::is_abstract_v<minix_type>, _composite_pattern_impl<minix_type>, minix_type>;
};


/*
 *	组合模式别名
 *	模板形参们 : minix_types ,需要被混入的接口们
 */
template <typename ... minix_types>
using composite_pattern_impl = typename _composite_pattern_impl<minix_types...>::result_type;

DESIGN_PATTERN_END