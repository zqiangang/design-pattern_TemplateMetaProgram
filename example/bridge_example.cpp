#include "../include/bridge.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

 //简易的 function 实现

template <typename Ret, typename ... Args>
class function_base_impl
{
public:
	virtual Ret invoke(Args&&...) = 0;
};

template <typename T, typename Ret, typename ...Args>
class function_impl : public function_base_impl<Ret, Args...>
{
private:
	T _invocable_object;
public:
	function_impl(T && invocable_obj)
		:_invocable_object(std::forward<T>(invocable_obj))
	{}

	virtual Ret invoke(Args&&... args) override
	{
		return _invocable_object(std::forward<Args>(args)...);
	}
};

template <typename T>
class simple_function;

template <typename Ret, typename ... Args>
class simple_function<Ret(Args...)>
{
public:
	using bridge_type = bridge_pattern_impl<function_base_impl<Ret, Args...>>;			// 使用桥接框架
	simple_function()
		: _bridge_impl(new bridge_type())
	{}

	template <typename T>
	simple_function(T&& object)
	{
		_bridge_impl = new bridge_type();		// 实例化侨界框架
		using save_type = std::decay_t<T>;
		using bridge_spec_impl = function_impl<save_type, Ret, Args...>;
		//_bridge_impl = new bridge_spec_impl(std::forward<T>(object));
		_bridge_impl->first<bridge_spec_impl>(std::forward<T>(object));					// 初始化要桥接的特定对象,并指名构造参数
	}

	Ret operator()(Args&& ... args)
	{
		return _bridge_impl->implementor()->invoke(std::forward<Args>(args)...);
	}

	virtual ~simple_function()
	{
		if (_bridge_impl != nullptr)
			delete _bridge_impl;
	}

private:
	bridge_type* _bridge_impl;
};

void hello(int)
{
	std::cout << "test simple function" << std::endl;
}

void test_bridge()
{
	// 普通函数
	simple_function<void(int)> sf(hello);
	sf(12);
	// 函数指针
	simple_function<void(int)> spf(&hello);
	spf(33);
	// lambda and all invocable object
	simple_function<void(int)> slf([](int v) {std::cout << "this is lambda and all invocable" << std::endl;; });
	slf(999);
}