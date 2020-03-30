#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_
#include "dp_tool_kits.hpp"
#include <iostream>
DESIGN_PATTERN_START

/*
 *		* ʹ�ü�� *
 *		* step.1 *
 *	���ȴ�����Ҫ����������
 *  �ο�ʹ�� singleton_example
 *		* step.2 *
 *	�����Լ��ĵ���ģʽ�� 
 *	�ο�ʹ�� singleton_example
 *		* step.3 *
 *  ʹ�ø�ģʽ, �ο�ʹ�� singleton_example
 *  
 *  ע�� : ��������ģʽ��ʵ�ֽṹ��ͬ ʹ�òο� singleton_example
 */

//#define DEFAULT_ENABLE_SECOND_SINGLETON

#ifndef DEFAULT_ENABLE_SECOND_SINGLETON

// ����ģʽ
// ģ���β� : base_type ����ģʽ�Ļ���
template <typename base_type>
class singleton_pattern_impl final: public base_type
{
	singleton_pattern_impl(singleton_pattern_impl const&) = delete;
	singleton_pattern_impl& operator=(singleton_pattern_impl const&) = delete;
protected:
	template <typename ... Args>
	singleton_pattern_impl(Args&& ... args)
		:base_type(std::forward<Args>(args)...)
	{

	}
public:
	using type = std::conditional_t<std::is_class_v<base_type> && std::is_pointer_v<base_type>, std::remove_cv_t<std::remove_pointer_t<base_type>>, std::remove_cv_t<base_type>>;
	using type_pointer = std::add_pointer_t<type>;
public:
	template <typename ... Args>
	static type_pointer Instance(Args&& ... args)
	{
		if (singleton_instance == nullptr)
			singleton_instance = new singleton_pattern_impl(std::forward<Args>(args)...);
		return singleton_instance;
	}
private:
	static type_pointer singleton_instance;
};

template <typename base_type>
typename singleton_pattern_impl<base_type>::type_pointer singleton_pattern_impl<base_type>::singleton_instance = nullptr;

#else

template <typename derived_type>
class singleton_pattern_impl
{
	singleton_pattern_impl(singleton_pattern_impl const&) = delete;
	singleton_pattern_impl& operator=(singleton_pattern_impl const&) = delete;
protected:
	singleton_pattern_impl() = default;
	//friend derived_type;
public:
	using type = std::conditional_t<std::is_class_v<derived_type> && std::is_pointer_v<derived_type>, std::remove_cv_t<std::remove_pointer_t<derived_type>>, std::remove_cv_t<derived_type>>;
	using type_pointer = std::add_pointer_t<type>;
public:
	template <typename ... Args>
	static type_pointer Instance(Args&& ... args)
	{
		if (singleton_instance == nullptr)
			singleton_instance = new type(std::forward<Args>(args)...);
		return singleton_instance;
	}
private:
	static type_pointer singleton_instance;
};

template <typename derived_type>
typename singleton_pattern_impl<derived_type>::type_pointer singleton_pattern_impl<derived_type>::singleton_instance = nullptr;

#endif // !DEFAULT_ENABLE_FIRST_SINGLETON

DESIGN_PATTERN_END
#endif // !_SINGLETON_HPP_
