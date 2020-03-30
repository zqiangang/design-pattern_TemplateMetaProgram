#ifndef _PROTOTYPE_HPP_
#define _PROTOTYPE_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *		* ʹ�ü�� *
 *		* step.1 *
 *  ���ȴ����Զ���� hack_method �� minix_types 
 *      * step.2 *
 *	�����Լ�������,����������Ҫ����һЩ������̵ķ���,�������ǿ���ͨ��
 *  ģ������������������ǽ��н���
 *	�ο�ʹ�� prototype_example
 *		* step.3 *
 *	ָ�� hack_method ʹ��Ĭ�ϵĻ��Զ���� hack_method
 *  �ο�ʹ�� prototype_example
 *		* step.4 *
 * ʹ�ø�ģʽ, �ο�ʹ�� prototype_example
 */

template <typename derived_type>
class default_prototype_hack_method
{
public:
    using type = std::conditional_t<std::is_pointer_v<derived_type>, std::remove_cv_t<std::remove_pointer_t<derived_type>>, std::remove_cv_t<derived_type>>;
    using type_pointer = std::add_pointer_t<type>;
	virtual type_pointer clone() = 0;
};

/*
 *	ԭ��ģʽ
 *	ģ��ģ���β� : hack_method, ʹ�õ� hack_method,��ʹ��Ĭ�ϵ� default_prototype_hack_method  ʱ,Ҫ������
 *				 : ���ö����Լ��� hack method ʱ,���� ����һ�����ǵ�һ��ģ�����Ϊ build_object
 *	ģ��ģ���������� : ��ʹ��Ĭ�ϵ� hack_method ,�����ģ��ģ���ǿ���ͨ��ģ���βκ������Ļ������Ĭ�� hack_method 
 *					   : �Ĺ��з��������ݽ���
 */

template <template <typename> class hack_method = default_prototype_hack_method,
	template <typename> class ... minix_types>
class prototype_pattern_impl : 
	public hack_method<prototype_pattern_impl<hack_method,minix_types...>>,
	public sequence_template_inherit<prototype_pattern_impl<hack_method,minix_types...>,minix_types...>
{
public:
};

DESIGN_PATTERN_END
#endif // !_PROTOTYPE_HPP_
