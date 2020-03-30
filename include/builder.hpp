#ifndef _BUILDER_HPP_
#define _BUILDER_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *		* ʹ�ü�� *
 *		* step.1 *
 *	����ָ���������� ,Ȼ��ָ����ʹ�õ� hack_method,Ĭ�ϵĻ��Լ������ 
 *  �ο�ʹ�� builder_example
 *		* step.2 *
 *	�����Լ�������,����������Ҫ����һЩ������̵ķ���
 *	�ο�ʹ�� builder_example
 *		* step.3 *
 * ʹ�ø�ģʽ, �ο�ʹ�� builder_example
 */

/*
 *	���� : �ṩĬ�ϵ� hack_method ����, ��һЩ������ͨ�ò�����
 *  ģ���β� : build_method , ��Ҫ����Ķ���
 */
template <typename build_object>
class default_builder_hack_method
{
public:
	using type = std::conditional_t<std::is_pointer_v<std::remove_cv_t<build_object>>, std::remove_pointer_t<build_object>, std::remove_cv_t<build_object>>;
	using type_pointer = std::add_pointer_t<type>;
	using type_pointer_ref = std::add_lvalue_reference_t<type_pointer>;
public:
	virtual void first()							// Ĭ�ϳ�ʼ������,Ҫ��build_object ��Ĭ�Ϲ��캯��
	{
		get_build_object() = new build_object();
	}
	type_pointer result()const						// ��ȡ���յĽ�����
	{
		return m_build_object;
	}
	type_pointer get_build_object()const			// ���ں��������������,�������������ṩ���ʹ���
	{
		return m_build_object;
	}
protected:
	type_pointer_ref get_build_object()				// ���ڼ̳����д��ͷ��ʲ���
	{
		return m_build_object;
	}
private:
	type_pointer m_build_object;
};

/*
 *	������ģʽ
 *	ģ���β� : build_object, ��ʹ��Ĭ�ϵ� default_builder_hack_method ʱ,Ҫ�� build_object ��Ĭ�Ϲ���
 *			 : ����,����,Ӧ���ض��� first ����,��ʼ�� build_object �����ݳ�Ա,��ʹ���Զ���� hack_method
 *	ģ��ģ���β� : hack_method, ʹ�õ� hack_method,��ʹ��Ĭ�ϵ� default_builder_hack_method  ʱ,Ҫ������
 *				 : ���ö����Լ��� hack method ʱ,���� ����һ�����ǵ�һ��ģ�����Ϊ build_object 
 *	ģ��ģ���������� : ��ʹ��Ĭ�ϵ� hack_method ,�����ģ��ģ���ǿ���ͨ�� get_build_object(),ʵ�ֶ� build-
 *					   : object �Ķ�����
 *	����Լ�� : build_object Ӧ����һ�� class ����
 */
template <typename build_object,
	template<typename> class hack_method = default_builder_hack_method,
	template<typename> class ... minix_types>
class builder_pattern_impl : 
	public hack_method<build_object>,
	public sequence_template_inherit<builder_pattern_impl<build_object,hack_method,minix_types...>,minix_types...>
{
	static_assert(std::is_class_v<build_object>, "build_object is not an class type");
};


DESIGN_PATTERN_END
#endif // !_BUILDER_HPP_
