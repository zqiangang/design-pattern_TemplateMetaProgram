#ifndef _STRATEGY_HPP_
#define _STRATEGY_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	作用 : 提供一些默认的方法和数据成员
 *  模板形参 : context , 使用策略对象的上下文对象
*/
template <typename context>
class default_strategy_hack_method
{
public:
	virtual void first(context* ctxt)
	{
		_context = ctxt;
	}
	virtual void compose() = 0;
	virtual ~default_strategy_hack_method(){}
protected:
	virtual context*& get_context()
	{
		return _context;
	}
private:
	context* _context;
};

/*
 *	策略模式
 *	模板形参 : context , 上下文对象类型
 *	模板模板形参 : hack_method , 提供一些默认的方法和数据成员
 *  模板模板形参们 : 提供用户所定义的方法和数据成员
 *  断言约束 : context , 应当是一个 class 类型
*/
template <typename context,
	template <typename> class hack_method = default_strategy_hack_method,
	template <typename> class ... minix_types>
class strategy_pattern_impl :
	public hack_method<context>,
	public sequence_template_inherit<strategy_pattern_impl<context,hack_method,minix_types...>,minix_types...>
{
	static_assert(std::is_class_v<context>, "context should is an class type");
};

DESIGN_PATTERN_END
#endif // !_STRATEGY_HPP_
