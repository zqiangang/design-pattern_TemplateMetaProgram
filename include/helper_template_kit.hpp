#ifndef _HELPER_TEMPLATE_KIT_HPP_
#define _HELPER_TEMPLATE_KIT_HPP_
#include "dp_macro.hpp"

DESIGN_PATTERN_START

class NilType{};

// ��������ģ��
template <template <typename > class ... template_paras>
struct count
{
	static constexpr auto value = sizeof...(template_paras);
};


template <template <typename > class ... template_paras>
constexpr auto count_v = count<template_paras...>::value;

template <typename ...types>
struct type_count
{
	static constexpr auto value = sizeof...(types);
};

template <typename ...types>
struct any_types;

template <typename ... types>
struct type_count<any_types<types...>>
{
	static constexpr auto value = sizeof...(types);
};

template <typename ... types>
constexpr auto type_count_v = type_count<types...>::value;

// �������������

// ���ģ����������ݹ���
template <typename ... types>
struct any_types{};
// �����ײ�Ԫ��
template <typename>
struct pop_front;

template <typename head, typename ... paras>
struct pop_front<any_types<head, paras...>>
{
	using type = any_types<paras...>;
};

template <>
struct pop_front<any_types<>>
{
	using type = any_types<>;
};

template <typename any_t>
using pop_front_t = typename pop_front<any_t>::type;

// ��ȡ�ײ�Ԫ��
template <typename>
struct front;

template <typename hd,typename ... types>
struct front<any_types<hd,types...>>
{
	using type = hd;
};

template <>
struct front<any_types<>>
{
	using type = any_types<>;
};

template <typename type_pack>
using front_t = typename front<type_pack>::type;

// ���Ԫ�ص��ײ�
template <typename,typename>
struct push_front;

template <typename element, typename ... types>
struct push_front<element, any_types<types...>>
{
	using type = any_types<element, types...>;
};

template <typename element>
struct push_front<element, any_types<>>
{
	using type = any_types<element>;
};

template <typename element, typename any_t>
using push_front_t = typename push_front<element, any_t>::type;

template <typename,typename>
struct has_element;

template <typename element,typename head,typename ... types>
struct has_element<element, any_types<head,types...>>
{
	static constexpr auto value = std::is_same_v<element, head> || has_element<element, any_types<types...>>::value;
};

template <typename element>
struct has_element<element, any_types<>>
{
	static constexpr auto value = false;
};

template <typename element,typename any_t>
constexpr auto has_element_v = has_element<element, any_t>::value;

// һ���ܲ�һ����,ȥ��
template <typename>
struct carrot_hole;

template <typename head,typename... types>
struct carrot_hole<any_types<head,types...>>
{
private:
	using head_t = head;
	using tail_t = typename carrot_hole<any_types<types...>>::type;
public:
	using type = std::conditional_t<has_element_v<head_t,tail_t>,tail_t,push_front_t<head_t,tail_t>>;
};

template <typename head>
struct carrot_hole<any_types<head>>
{
	using type = any_types<head>;
};

// ��ͨ��ת ��ģ�������ģ�����ģ����ʽ
template <typename... types>
class translate_simple_tt
{
public:
	template <typename T>
	class result_type : public types...
	{

	};
};



// �ָ� any_t,ʹ�ô�ģ����� Ԫ��һ�������� any_t ��
template <typename,typename>
struct split;
// �� any_type ʱ
template <typename element>
struct split<element, any_types<>>
{
	using split_type = element;
	using forward_types = any_types<>;
	using back_types = any_types<>;
};

// ��������ʱ
//double, float, int, char, char
template <typename element,typename head, typename ... types>
struct split<element, any_types<head,types...>>
{
private:
	using head_t = head;
	using new_for_t = std::conditional_t<std::is_same_v<element,head_t>, any_types<>, typename split<element, any_types<types...>>::forward_types>;
public:
	using split_type = element;
	using back_types = std::conditional_t<std::is_same_v<element, head_t>, any_types<head_t, types...>,typename split<element, any_types<types...>>::back_types>;
	using forward_types = std::conditional_t<std::is_same_v<element, head_t>, any_types<>, push_front_t<head_t,new_for_t>>;
};

template <typename element, typename head>
struct split<element, any_types<head>>
{
public:
	using split_type = element;
	using forward_types = any_types<>;
	using back_types = any_types<head>;
};

// compare ����
template<typename T,T a,T b>
struct is_less
{
	static constexpr auto value = a < b;
};

template<typename T, T a, T b>
struct is_equal
{
	static constexpr auto value = a == b;
};

template<typename T, T a, T b>
constexpr auto is_less_v = is_less<T, a, b>::value;

template<typename T,T a,T b>
constexpr auto is_equal_v = is_equal<T, a, b>::value;


// ����ʱ����
// ����Ӧ�ĳ�Ա�Ƿ����
template <typename F, typename ... Args,
	typename = decltype(std::declval<F>()(std::declval<Args&&>() ...))>
std::true_type is_valid_impl(void*);

template <typename,typename...>
std::false_type is_valid_impl(...);

/*
 *	�����
 *  ʹ�÷��� :  �����û���ⷽ��
 *			 :	����û��ṩ��Ҫ�����Ķ���
 *	�ο�	 :	has_factory_method
 */

struct is_valid
{
	template <typename T>
	static constexpr auto check(T lambda)
	{
		return [lambda](auto&& ... args)
		{
			return decltype(is_valid_impl<decltype(lambda), decltype(args) && ...>(nullptr)){};
		};
	}
};

template <typename T>
struct Type
{
	using type = T;
};

template <typename T>
constexpr auto type_object = Type<T>{};

template <typename T>
T* type_value_as_pointer(Type<T>);

/*	factory_method ���ʹ��Ĭ�ϵ�minix ��ʱ, �û��ṩ�� hack ���Ƿ���ϱ�׼
 *	�� : �û��ṩ�� hack ��Ӧ������ factory_method ���Լ������
 *  ע : �û��ṩ��hack �ȿ����Ƿǳ����Ҳ����ʱ����ģ�����ʹ��ָ�룬��ֹ���ܴ�������
 *	   : ���������
 */
// ����ʱ����
auto has_default_constructible = is_valid::check
(
	[](auto x) -> decltype((void)decltype(type_value_as_pointer(x))()){}
);

// ����ʧ�ܷ�������

template<bool stat>
struct assert_stat
{
	static_assert(stat,__FILE__);
};

using assert_failure = assert_stat<false>;
using assert_success = assert_stat<true>;

 //factory method ���
template <typename T, typename = std::void_t<>>
struct has_factory_method : std::false_type {};

template <typename T>
struct has_factory_method<T, std::void_t<decltype(std::declval<T>().factory_method())>> : std::true_type {};

template <typename T>
constexpr auto has_factory_method_v = has_factory_method<T>::value;

// type brush  ����ˢ��
template <typename condinate>
class type_brush
{
public:

};

DESIGN_PATTERN_END

#endif // !_HELPER_TEMPLATE_KIT_HPP_
