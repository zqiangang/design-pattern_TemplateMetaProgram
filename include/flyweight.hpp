#ifndef _FLYWEIGHT_HPP_
#define _FLYWEIGHT_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	享元模式实现
 *  模板形参们 : flyweight_minix , 对于 享元对象所要混入的方法或数据成员等
 *  断言约束 : flyweight_minix 的混入对象应当是 class 类型
 *			 : 如果定义了 ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC ,那么 flyweight_minix 中至少存在一个元素是 多态的 
 *	成员类型 : result_type 混入 flyweight_minix 后得到的结果类型 
 */
template <typename ... flyweight_minixs>
class _flyweight_pattern_impl : public sequence_minixs_inherit<flyweight_minixs...>
{
	static_assert(std::conjunction_v<std::is_class<flyweight_minixs>...>, "found element type of flyweight_minixs has an non class type");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::disjunction_v<std::is_polymorphic<flyweight_minixs>...>, "factory inherit all class element of flyweight_minixs,the result class must be polymorphic");
#endif
public:
	using result_type = _flyweight_pattern_impl<flyweight_minixs...>;
};

/*
 *  享元模式特化
 *	模板形参 : flyweight_object ,混入的类型,该类型提供方法和成员
 *  断言约束 : flyweight_object ,应当是一个 class 类型
 *			 : 如果定义 ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC , 那么 flyweight_object 应当是多态的
 *  成员类型 : result_type , 如果 flyweight_object 那么 result_type 就是 flyweight_pattern_impl<flyweight_object>
 *			 : 否则 result_type 为 flyweight_object 模板形参类型
 */
template <typename flyweight_object>
class _flyweight_pattern_impl<flyweight_object> : public flyweight_object
{
	static_assert(std::is_class_v<flyweight_object>, "flyweight is not a class type");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::is_polymorphic_v<flyweight_object>, "factory inherit all class element of flyweight_minixs,the result class must be polymorphic");
#endif
public:
	using result_type = std::conditional_t<std::is_abstract_v<flyweight_object>, _flyweight_pattern_impl<flyweight_object>, flyweight_object>;
};

template <typename ... flyweight_minixs>
using flyweight_pattern_impl = typename _flyweight_pattern_impl<flyweight_minixs...>::result_type;

/*
 *	作用 : 提供默认的 hack_method 方法, 如一些基本的通用操作等
 *  模板形参 : flyweight , 享元对象
 *  变量形参 : flyweight_count , 内部存储的最大享元对象数量
 */
template <typename flyweight, int flyweight_count>
class default_flyweight_factory_hack_method
{
public:
	default_flyweight_factory_hack_method() :								// 默认构造函数,初始化 _flyweight_objects 为 nullptr
		_flyweight_objects(nullptr)
	{}

	virtual void first()													// 初始化函数,初始化 _flyweight_object 为 flyweight_count 容量的数组
	{
		if (_flyweight_objects == nullptr)
			_flyweight_objects = new flyweight*[flyweight_count]{ nullptr };
	}
	
	template<typename share_flyweight, typename Key, typename ...Args>		// 获取享元对象通过 key 值,不存在则创建并加入到_flyweight_objects
	flyweight * get_shared_flyweight(Key const& key, Args&& ... args)
	{
		if (!_flyweight_objects[key])
			_flyweight_objects[key] = new share_flyweight(std::forward<Args>(args)...);
		return _flyweight_objects[key];
	}

	template <typename non_share_flyweight,typename ... Args>
	flyweight* create_non_shared_flyweight(Args && ... args)const			// 创建享元对象中的非共享部分
	{
		return new non_share_flyweight(std::forward<Args>(args)...);
	}

private:
	flyweight** _flyweight_objects;
};

/*
 *	享元工厂
 *	模板形参 : flyweight , 享元对象基类,如果没有自定义基类一般是 flyweight_pattern_impl,详见 flyweight_pattern_impl
 *  变量形参 : flyweight_count , 指明 default_flyweight_factory_hack_method,内部最大存储的享元对象数量
 *  模版模版形参 : hack_method , 默认提供的一些享元工厂的基本操作,可以自定义自己的 hack_method ,但要符合模板形参约束
 *				 : minix_types , 一些用户需要的操作,通过此模板形参混入 flyweight_factory ,混入方法可以任意
 *  断言约束 : flyweight_count 不应该小于等于 0
 */
template <typename flyweight, int flyweight_count = 16,
	template <typename, int> class hack_method = default_flyweight_factory_hack_method,
	template <typename> class ... minix_types>
class flyweight_factory_pattern_impl : 
	public hack_method<flyweight, flyweight_count>,
	public sequence_template_inherit<flyweight_factory_pattern_impl<flyweight,flyweight_count,hack_method,minix_types...>,minix_types...>
{
	static_assert(is_less_v<int, 0, flyweight_count>, "flyweight count less and equal 0");
};

DESIGN_PATTERN_END
#endif // !_FLYWEIGHT_HPP_
