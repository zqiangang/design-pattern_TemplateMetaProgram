#ifndef _FACTORY_METHOD_HPP_
#define _FACTORY_METHOD_HPP_
#include <iostream>
#include "dp_tool_kits.hpp"
#include "sequence_minix.hpp"
DESIGN_PATTERN_START
/*
 *		* 使用简介 *
 *		* step.1 *
 *	首先创建自己的 productor 混入(单个或多个)抽象基类, 参考 factory_method_example
 *		* step.2 *
 *	创建自己的 hack 和 minix 抽象类,或使用 默认的 default_hack_factory_method 和 default_factory_method_minix
 *  分别作为默认的 hack_method 和 默认的 minix_types 
 *	hack 提供自定义的抽象工厂方法,该方法在不同的子类被重定义
 *	minix 提供依赖于 hack 的抽象方法的方法 -> 调用抽象方法完成自己的功能
 *	参考使用 factory_method_example 
 *		* step.3 *
 *	创建 productor 和 creator 分别作为 factory_method pattern 的 产品和创建者抽象基类
 *	参考使用 factory_method_example 
 *		* step.4 "
 * 使用该模式, 参考使用 factory_method_example 
 * 
 *  tips : 如果您需求一个有较多工厂方法的 hack_method ,那么你只需要定义自己的 hack_method 和 相对应的  minix 们
 *       : 注意自定义的 hack_method 必须符合 template<typename> class 的声明,无论是否对这个模板形参是否有需求
 *       : 此时 , 根据自定义的 hack_method 对 product 的需求情况,决定是否使用对应的 productor 或 不需要该模版形参
         : 使用 give_up_this_productor 或 任意其他类型
 */

    class give_up_this_productor{};

/*
 *	默认提供的混入类
 *	主要功能 : 调用默认提供的 factory_method 方法
 *  模板形参 : 奇异递归模版,该模板形参是支撑该模板的派生类,主要功能是,提供一个调用其他混入类公有
 *           : 方法的一个窗口
 */
template <typename derived_type>
class default_factory_method_minix
{
public:
	virtual void default_call_factory_method()
	{
		std::cout << "default call factory method" << std::endl;
		static_cast<derived_type*>(this)->factory_method();
	}
};

/*
 *	默认提供的 hack 类
 *  主要功能 : 默认提供抽象的 factory method
 *  模板形参 : Product 要求实例化该类应当提供对应的抽象产品基类类型，作为 factory_method 的返回值指针类型
 */
template <typename product>
class default_hack_factory_method
{
public:
	using product_type = std::conditional<std::is_pointer_v<std::remove_cv_t<product>>, std::remove_pointer_t<product>, std::remove_cv_t<product>>;
	using product_point = std::add_pointer_t<product_type>;
	virtual product_point factory_method() = 0;
};

/*
 *  工厂方法模式 - 创建者
 *	模板形参      : product_object	, 所要创建的产品基类
 *	模板模板形参  : hack_method, 工厂方法的提供者,参考 default_hack_factory_method 注释
 *	模板模板形参  : minix_types... , 要被混入的参数类们，他们提供了方法，尤其是 其中应当至少存在一个与 hack_method 相关的 类
 *  静态断言 1	  : 传入的 hack_factory_method 模板参数应当符合 is_class 断言
 *  静态断言 2	  : 仅当 ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC 被定义时生效
 *				  : 检查是否模板模板参数由当前类型定义出类型时,这个基类应当是符合 is_polymorphic 断言
 */
template <typename product_object,
    template <typename> class hack_method = default_hack_factory_method,
	template <typename> class ... minix_types>
class factory_method_pattern_creator_impl : 
	public hack_method<product_object>,
	public sequence_template_inherit<factory_method_pattern_creator_impl<product_object,hack_method, minix_types...>, minix_types...>
{
private:
	static_assert(std::is_class_v<hack_method<product_object>>, "_factory_method is not a class or struct type,it is not could inherited");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	using base_type = sequence_template_inherit<factory_method_pattern_creator_impl<product_object,hack_method, minix_types...>, minix_types...>;
	static_assert(std::is_polymorphic_v<base_type>, R"(factory inherit all class element of concrete template when sequence_template_inherit
		proformance complete,the result class must be polymorphic)");
#endif
};


/*
 *  工厂方法模式 - 产品
 *  模板形参 : 混入类,用minix_types 的成员 构造 productor
 *  静态断言 : 要求将要混入的类中，至少有一个是符合 is_polymorpic 断言
 */
template <typename ... minix_types>
class factory_method_pattern_product_impl : public sequence_minixs_inherit<minix_types...>
{
private:
	static_assert(std::conjunction_v<std::is_class<minix_types>...>, "all element type of minix_types ,must be is class type");
    static_assert(!std::conjunction_v<std::is_empty<minix_types>...>, "all element type of minix_types is empty class");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::disjunction_v<std::is_polymorphic<minix_types> ...>, "factory inherit all class element of minix_types,the result class must be polymorphic");
#endif
};


/*
 *  别名模板,快速创建 factory_method 的 creator
 *  当传入的模板模板参数个数为 0 个时
 *  检查用户提供的 hack 是否存在约定方法 factory_method,不存在,则返回断言失败类型
 *  模板参数的数量不为 0 时，则正常返回用户的构造类型
 */
template <typename product_object,
    template <typename> class hack_method = default_hack_factory_method,
	template <typename> class ... minix_types>
using factory_method_creator = std::conditional_t<count_v<minix_types...> == 0,
    std::conditional_t<has_factory_method_v<hack_method<product_object>>,
	factory_method_pattern_creator_impl<product_object,hack_method,default_factory_method_minix>,assert_failure>,
	factory_method_pattern_creator_impl<product_object,hack_method, minix_types...>>;


/*
 *  别名模板,快速创建 factory_method 的 productor
 *  详细参考 factory_method_pattern_product_impl
 */
template <typename ... minix_types>
using factory_method_productor = factory_method_pattern_product_impl<minix_types...>;





DESIGN_PATTERN_END
#endif // !_FACTORY_METHOD_HPP_

