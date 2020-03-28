#ifndef _BUILDER_HPP_
#define _BUILDER_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *		* 使用简介 *
 *		* step.1 *
 *	首先指明创建对象 ,然后指明所使用的 hack_method,默认的或自己定义的 
 *  参考使用 builder_example
 *		* step.2 *
 *	创建自己混入类,混入类们主要包含一些建造过程的方法
 *	参考使用 builder_example
 *		* step.3 *
 * 使用该模式, 参考使用 builder_example
 */

/*
 *	作用 : 提供默认的 hack_method 方法, 如一些基本的通用操作等
 *  模板形参 : build_method , 所要建造的对象
 */
template <typename build_object>
class default_builder_hack_method
{
public:
	using type = std::conditional_t<std::is_pointer_v<std::remove_cv_t<build_object>>, std::remove_pointer_t<build_object>, std::remove_cv_t<build_object>>;
	using type_pointer = std::add_pointer_t<type>;
	using type_pointer_ref = std::add_lvalue_reference_t<type_pointer>;
public:
	virtual void first()							// 默认初始化操作,要求build_object 有默认构造函数
	{
		get_build_object() = new build_object();
	}
	type_pointer result()const						// 获取最终的建造结果
	{
		return m_build_object;
	}
	type_pointer get_build_object()const			// 用于和其他混入类合作,向其他混入类提供访问功能
	{
		return m_build_object;
	}
protected:
	type_pointer_ref get_build_object()				// 用于继承类的写入和访问操作
	{
		return m_build_object;
	}
private:
	type_pointer m_build_object;
};

/*
 *	建造者模式
 *	模板形参 : build_object, 当使用默认的 default_builder_hack_method 时,要求 build_object 有默认构造
 *			 : 函数,否则,应当重定义 first 函数,初始化 build_object 的数据成员,或使用自定义的 hack_method
 *	模板模板形参 : hack_method, 使用的 hack_method,当使用默认的 default_builder_hack_method  时,要求如上
 *				 : 当用定义自己的 hack method 时,遵守 至少一个且是第一个模板参数为 build_object 
 *	模板模板混入参数门 : 当使用默认的 hack_method ,混入的模板模板们可以通过 get_build_object(),实现对 build-
 *					   : object 的读操作
 *	断言约束 : build_object 应当是一个 class 类型
 */
template <typename build_object,
	template<typename> class hack_method = default_builder_hack_method,
	template<typename> class ... minix_types>
class builder_pattern_impl : 
	public hack_method<build_object>,
	public sequence_template_inherit<builder_pattern_impl<build_object,hack_method,minix_types...>,minix_types...>
{
	static_assert(std::is_class_v<build_object>, "build_object is not an class type");
};


DESIGN_PATTERN_END
#endif // !_BUILDER_HPP_
