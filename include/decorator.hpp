#ifndef _DECORATOR_HPP_
#define _DECORATOR_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	作用 : 提供默认的 hack_method 方法, 如一些基本的通用操作等
 *  模板形参 : component_object , 装饰器的基类,和被装饰的类共同基类,作为 default_decorator_hack_method
 *			 : 的基类
 */
template <typename component_object>
class default_decorator_hack_method : public component_object
{
public:
	default_decorator_hack_method()								// 默认构造函数,把 _component 初始化为 nullptr
		: _component(nullptr)
	{}

	template <typename concrete_component,typename ... Args>	// 初始化操作,初始化当前装饰器要装饰的对象
	void first(Args&& ... args)
	{
		_component = new concrete_component(std::forward<Args>(args)...);
	}

	void first(component_object * object)
	{
		_component = object;
	}

	component_object* component()
	{
		return _component;
	}

	virtual ~default_decorator_hack_method()					// 析构函数,当 _component 不为 nullptr 时,释放 _component
	{
		if (_component != nullptr)
			delete _component;
	}
private:
	component_object* _component;
};

/*
 *	装饰模式
 *	模板形参 : component_object , 装饰器的基类,和被装饰的类共同基类
 *  模板模板形参 : hack_method , 默认的 hack_method 方法,用于提供一些基本的操作,详见 default_decorator_hack_method
 *  断言约束 : component_object 应当是一个 class 类型,且不应当为 empty class
 *	宏		 : 当 ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC 定义式,启用多态断言约束
 */
template <typename component_object,
	template <typename> class hack_method = default_decorator_hack_method>
class decorator_pattern_impl : public hack_method<component_object>
{
	static_assert(std::is_class_v<component_object>, "component object must be a class type");
	static_assert(!std::is_empty_v<component_object>, "component object should is empty class");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::is_polymorphic_v<component_object>, "implementor_object must be polymorphic");
#endif
};

DESIGN_PATTERN_END
#endif // !_DECORATOR_HPP_
