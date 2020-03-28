#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	作用 : hack_method 方法
 *	提供一些基本的方法
 */
template<typename observer_object>
class default_observer_subject_hack_method
{
public:
	virtual void add_observer(observer_object* observer) = 0;
	virtual void remove_observer(observer_object* observer) = 0;
	virtual void notify()const = 0;
};

/*
 *	观察者模式 被观察者
 *  模板形参 : observer_object , 观察者对象的基类
 *	模版模版形参 : 提供一些基本的方法
 *	模版模版形参列表 : 提供一些用户自定义的方法
 */
template <typename observer_object,
	template <typename> class hack_method = default_observer_subject_hack_method,
	template <typename> class ... minix_types>
class observer_patterm_subject_impl :
	public hack_method<observer_object> ,
	public sequence_template_inherit<
	observer_patterm_subject_impl<observer_object, hack_method, minix_types...>, minix_types...>
{
	static_assert(std::is_class_v<observer_object>, "observer object must be class type");
};

/*
 *	作用 : 提供一些基本的观察者方法
 */
template <typename subject_object>
class default_observer_observer_hack_method
{
public:
	virtual void update(const subject_object*) = 0;
};

/*
 *	观察者模式 观察者
 *  模板形参 : subject_object 被观察者的基类
 *	模板模板形参 : 提供一些基本的观察者方法
 *  模板模板形参列表 : 提供一些用户自定义的方法
*/
template <typename subject_object,
	template <typename> class hack_method = default_observer_observer_hack_method,
	template <typename> class ... minix_types>
class observer_pattern_observer_impl : 
    public hack_method<subject_object>,
    public sequence_template_inherit<
        observer_pattern_observer_impl<subject_object,hack_method,minix_types...>,minix_types...>
{
	static_assert(std::is_class_v<subject_object>, "subiect object must be class type");
};

DESIGN_PATTERN_END
#endif // !_OBSERVER_HPP_
