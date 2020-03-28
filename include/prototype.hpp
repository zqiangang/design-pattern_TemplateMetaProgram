#ifndef _PROTOTYPE_HPP_
#define _PROTOTYPE_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *		* 使用简介 *
 *		* step.1 *
 *  首先创建自定义的 hack_method 或 minix_types 
 *      * step.2 *
 *	创建自己混入类,混入类们主要包含一些建造过程的方法,混入类们可以通过
 *  模板参数和其他混入类们进行交互
 *	参考使用 prototype_example
 *		* step.3 *
 *	指明 hack_method 使用默认的或自定义的 hack_method
 *  参考使用 prototype_example
 *		* step.4 *
 * 使用该模式, 参考使用 prototype_example
 */

template <typename derived_type>
class default_prototype_hack_method
{
public:
    using type = std::conditional_t<std::is_pointer_v<derived_type>, std::remove_cv_t<std::remove_pointer_t<derived_type>>, std::remove_cv_t<derived_type>>;
    using type_pointer = std::add_pointer_t<type>;
	virtual type_pointer clone() = 0;
};

/*
 *	原型模式
 *	模板模板形参 : hack_method, 使用的 hack_method,当使用默认的 default_prototype_hack_method  时,要求如上
 *				 : 当用定义自己的 hack method 时,遵守 至少一个且是第一个模板参数为 build_object
 *	模板模板混入参数们 : 当使用默认的 hack_method ,混入的模板模板们可以通过模板形参和其他的混入类和默认 hack_method 
 *					   : 的公有方法和数据交互
 */

template <template <typename> class hack_method = default_prototype_hack_method,
	template <typename> class ... minix_types>
class prototype_pattern_impl : 
	public hack_method<prototype_pattern_impl<hack_method,minix_types...>>,
	public sequence_template_inherit<prototype_pattern_impl<hack_method,minix_types...>,minix_types...>
{
public:
};

DESIGN_PATTERN_END
#endif // !_PROTOTYPE_HPP_
