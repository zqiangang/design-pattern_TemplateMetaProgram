#ifndef _ADAPTER_HPP_
#define _ADAPTER_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *		* ʹ�ü�� *
 *		* step.1 *
 *	����ָ����Ҫ������Ķ���,Ȼ��ָ�������Լ��� hack_method ��ʹ��Ĭ�ϵ�
 *  �ο�ʹ�� adapter_example
 *		* step.2 *
 *	ָ��Ҫ������Ľӿ� 
 *	�ο�ʹ�� adapter_example
 *		* step.3 *
 * ʹ�ø�ģʽ, �ο�ʹ�� adapter_example
 */

// adaptee_box
template <typename>
class adaptee_box_impl;

// ������Ҫ��������࣬���еݹ�̳д洢
// ͨ�� get ��  set �����Դ洢���ض�����з��ʺ��޸�
template <typename ... adaptees>
class adaptee_box : public adaptee_box_impl<typename carrot_hole<any_types<adaptees...>>::type>
{
public:
	adaptee_box() = default;
	template <typename T, typename = std::enable_if_t<has_element_v<T, typename carrot_hole<any_types<adaptees...>>::type>> >
	void set(T* v)
	{
		using carrot_type = typename carrot_hole<any_types<adaptees...>>::type;
		// ·���и�
		using path_type = typename split<T, carrot_type>::back_types;
		// target path
		using tar_path = adaptee_box_impl<path_type>;
		// ���ö�Ӧ�ĺ���
		this->tar_path::_set(v);
	}

	template <typename T, typename = std::enable_if_t<has_element_v<T, typename carrot_hole<any_types<adaptees...>>::type>>>
	T* get()
	{
		using carrot_type = typename carrot_hole<any_types<adaptees...>>::type;
		// ·���и����
		using path_type = typename split<T, carrot_type>::back_types;
		// target path
		using tar_path = adaptee_box_impl<path_type>;
		// ���ö�Ӧ�ĺ���
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
		if constexpr(type_count_v<init_types> != 0)			// ����������Ϊ 0 ��ʱ��ֹͣ�ݹ����
		{
			using front_type = front_t<init_types>;
			_adaptee_box->set<front_type>(new front_type());		// ����Ĭ�Ϲ��캯��

			_first<pop_front_t<init_types>>();			// �ݹ��������
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
