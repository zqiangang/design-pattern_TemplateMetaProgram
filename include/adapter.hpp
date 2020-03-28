#ifndef _ADAPTER_HPP_
#define _ADAPTER_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *		* 使用简介 *
 *		* step.1 *
 *	首先指明需要被适配的对象,然后指明创建自己的 hack_method 或使用默认的
 *  参考使用 adapter_example
 *		* step.2 *
 *	指明要被适配的接口 
 *	参考使用 adapter_example
 *		* step.3 *
 * 使用该模式, 参考使用 adapter_example
 */

// adaptee_box
template <typename>
class adaptee_box_impl;

// 对所有要被适配的类，进行递归继承存储
// 通过 get 和  set 方法对存储的特定类进行访问和修改
template <typename ... adaptees>
class adaptee_box : public adaptee_box_impl<typename carrot_hole<any_types<adaptees...>>::type>
{
public:
	adaptee_box() = default;
	template <typename T, typename = std::enable_if_t<has_element_v<T, typename carrot_hole<any_types<adaptees...>>::type>> >
	void set(T* v)
	{
		using carrot_type = typename carrot_hole<any_types<adaptees...>>::type;
		// 路径切割
		using path_type = typename split<T, carrot_type>::back_types;
		// target path
		using tar_path = adaptee_box_impl<path_type>;
		// 调用对应的函数
		this->tar_path::_set(v);
	}

	template <typename T, typename = std::enable_if_t<has_element_v<T, typename carrot_hole<any_types<adaptees...>>::type>>>
	T* get()
	{
		using carrot_type = typename carrot_hole<any_types<adaptees...>>::type;
		// 路径切割完成
		using path_type = typename split<T, carrot_type>::back_types;
		// target path
		using tar_path = adaptee_box_impl<path_type>;
		// 调用对应的函数
		return this->tar_path::_get();
	}
};
 
template <typename head, typename ... adaptees>
class adaptee_box_impl<any_types<head, adaptees...>> : public adaptee_box_impl<any_types<adaptees...>>
{
	static_assert(std::is_class_v<head>, "found a type,is not a class type");
private:
	head* _adaptee;
protected:
	void _set(head* v)
	{
		this->_adaptee = v;
	}

	head* _get()
	{
		return  this->_adaptee;
	}
};

template <typename head>
class adaptee_box_impl<any_types<head>>
{
	static_assert(std::is_class_v<head>, "found a type,is not a class type");
private:
	head* _adaptee;
protected:
	void _set(head* v)
	{
		this->_adaptee = v;
	}

	head* _get()
	{
		return this->_adaptee;
	}
};

// hack_method
template <typename>
class default_adapter_hack_method;

template <typename ... adaptee_types>
class default_adapter_hack_method<adaptee_box<adaptee_types...>>
{
public:
	default_adapter_hack_method()
		:_adaptee_box(new adaptee_box<adaptee_types...>())
	{}
protected:
	template <typename init_types>
	void _first()const
	{
		if constexpr(type_count_v<init_types> != 0)			// 当参数个数为 0 个时，停止递归调用
		{
			using front_type = front_t<init_types>;
			_adaptee_box->set<front_type>(new front_type());		// 调用默认构造函数

			_first<pop_front_t<init_types>>();			// 递归调用自身
		}
	}
public:
	void first()
	{
		_first<any_types<adaptee_types...>>();
	}
	template <typename T>
	void first(T* val)const
	{
		_adaptee_box->set<T>(val);
	}
	template <typename spec_adaptee>
	spec_adaptee* adaptee()
	{
		return _adaptee_box->get<spec_adaptee>();
	}

	virtual ~default_adapter_hack_method()
	{
		if (_adaptee_box != nullptr)
		{
			delete _adaptee_box;
			_adaptee_box = nullptr;
		}
	}

private:
	adaptee_box<adaptee_types...>* _adaptee_box = nullptr;
};

template <typename adaptee_box,
	template <typename> class  = default_adapter_hack_method,
	template <typename> class ... >
class adapter_pattern_impl;

template <typename ...adaptees,
	template <typename> class hack_method,
	template <typename> class ... minix_types>
class adapter_pattern_impl<adaptee_box<adaptees...>, hack_method, minix_types...> :
	public hack_method<adaptee_box<adaptees...>>,
	public sequence_template_inherit<adapter_pattern_impl<adaptee_box<adaptees...>, hack_method, minix_types...>,minix_types...>
{

};

DESIGN_PATTERN_END
#endif // !_ADAPTER_HPP_
