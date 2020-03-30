#ifndef _FACTORY_METHOD_HPP_
#define _FACTORY_METHOD_HPP_
#include <iostream>
#include "dp_tool_kits.hpp"
#include "sequence_minix.hpp"
DESIGN_PATTERN_START
/*
 *		* ʹ�ü�� *
 *		* step.1 *
 *	���ȴ����Լ��� productor ����(��������)�������, �ο� factory_method_example
 *		* step.2 *
 *	�����Լ��� hack �� minix ������,��ʹ�� Ĭ�ϵ� default_hack_factory_method �� default_factory_method_minix
 *  �ֱ���ΪĬ�ϵ� hack_method �� Ĭ�ϵ� minix_types 
 *	hack �ṩ�Զ���ĳ��󹤳�����,�÷����ڲ�ͬ�����౻�ض���
 *	minix �ṩ������ hack �ĳ��󷽷��ķ��� -> ���ó��󷽷�����Լ��Ĺ���
 *	�ο�ʹ�� factory_method_example 
 *		* step.3 *
 *	���� productor �� creator �ֱ���Ϊ factory_method pattern �� ��Ʒ�ʹ����߳������
 *	�ο�ʹ�� factory_method_example 
 *		* step.4 "
 * ʹ�ø�ģʽ, �ο�ʹ�� factory_method_example 
 * 
 *  tips : ���������һ���н϶๤�������� hack_method ,��ô��ֻ��Ҫ�����Լ��� hack_method �� ���Ӧ��  minix ��
 *       : ע���Զ���� hack_method ������� template<typename> class ������,�����Ƿ�����ģ���β��Ƿ�������
 *       : ��ʱ , �����Զ���� hack_method �� product ���������,�����Ƿ�ʹ�ö�Ӧ�� productor �� ����Ҫ��ģ���β�
         : ʹ�� give_up_this_productor �� ������������
 */

    class give_up_this_productor{};

/*
 *	Ĭ���ṩ�Ļ�����
 *	��Ҫ���� : ����Ĭ���ṩ�� factory_method ����
 *  ģ���β� : ����ݹ�ģ��,��ģ���β���֧�Ÿ�ģ���������,��Ҫ������,�ṩһ���������������๫��
 *           : ������һ������
 */
template <typename derived_type>
class default_factory_method_minix
{
public:
	virtual void default_call_factory_method()
	{
		std::cout << "default call factory method" << std::endl;
		static_cast<derived_type*>(this)->factory_method();
	}
};

/*
 *	Ĭ���ṩ�� hack ��
 *  ��Ҫ���� : Ĭ���ṩ����� factory method
 *  ģ���β� : Product Ҫ��ʵ��������Ӧ���ṩ��Ӧ�ĳ����Ʒ�������ͣ���Ϊ factory_method �ķ���ֵָ������
 */
template <typename product>
class default_hack_factory_method
{
public:
	using product_type = std::conditional<std::is_pointer_v<std::remove_cv_t<product>>, std::remove_pointer_t<product>, std::remove_cv_t<product>>;
	using product_point = std::add_pointer_t<product_type>;
	virtual product_point factory_method() = 0;
};

/*
 *  ��������ģʽ - ������
 *	ģ���β�      : product_object	, ��Ҫ�����Ĳ�Ʒ����
 *	ģ��ģ���β�  : hack_method, �����������ṩ��,�ο� default_hack_factory_method ע��
 *	ģ��ģ���β�  : minix_types... , Ҫ������Ĳ������ǣ������ṩ�˷����������� ����Ӧ�����ٴ���һ���� hack_method ��ص� ��
 *  ��̬���� 1	  : ����� hack_factory_method ģ�����Ӧ������ is_class ����
 *  ��̬���� 2	  : ���� ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC ������ʱ��Ч
 *				  : ����Ƿ�ģ��ģ������ɵ�ǰ���Ͷ��������ʱ,�������Ӧ���Ƿ��� is_polymorphic ����
 */
template <typename product_object,
    template <typename> class hack_method = default_hack_factory_method,
	template <typename> class ... minix_types>
class factory_method_pattern_creator_impl : 
	public hack_method<product_object>,
	public sequence_template_inherit<factory_method_pattern_creator_impl<product_object,hack_method, minix_types...>, minix_types...>
{
private:
	static_assert(std::is_class_v<hack_method<product_object>>, "_factory_method is not a class or struct type,it is not could inherited");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	using base_type = sequence_template_inherit<factory_method_pattern_creator_impl<product_object,hack_method, minix_types...>, minix_types...>;
	static_assert(std::is_polymorphic_v<base_type>, R"(factory inherit all class element of concrete template when sequence_template_inherit
		proformance complete,the result class must be polymorphic)");
#endif
};


/*
 *  ��������ģʽ - ��Ʒ
 *  ģ���β� : ������,��minix_types �ĳ�Ա ���� productor
 *  ��̬���� : Ҫ��Ҫ��������У�������һ���Ƿ��� is_polymorpic ����
 */
template <typename ... minix_types>
class factory_method_pattern_product_impl : public sequence_minixs_inherit<minix_types...>
{
private:
	static_assert(std::conjunction_v<std::is_class<minix_types>...>, "all element type of minix_types ,must be is class type");
    static_assert(!std::conjunction_v<std::is_empty<minix_types>...>, "all element type of minix_types is empty class");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::disjunction_v<std::is_polymorphic<minix_types> ...>, "factory inherit all class element of minix_types,the result class must be polymorphic");
#endif
};


/*
 *  ����ģ��,���ٴ��� factory_method �� creator
 *  �������ģ��ģ���������Ϊ 0 ��ʱ
 *  ����û��ṩ�� hack �Ƿ����Լ������ factory_method,������,�򷵻ض���ʧ������
 *  ģ�������������Ϊ 0 ʱ�������������û��Ĺ�������
 */
template <typename product_object,
    template <typename> class hack_method = default_hack_factory_method,
	template <typename> class ... minix_types>
using factory_method_creator = std::conditional_t<count_v<minix_types...> == 0,
    std::conditional_t<has_factory_method_v<hack_method<product_object>>,
	factory_method_pattern_creator_impl<product_object,hack_method,default_factory_method_minix>,assert_failure>,
	factory_method_pattern_creator_impl<product_object,hack_method, minix_types...>>;


/*
 *  ����ģ��,���ٴ��� factory_method �� productor
 *  ��ϸ�ο� factory_method_pattern_product_impl
 */
template <typename ... minix_types>
using factory_method_productor = factory_method_pattern_product_impl<minix_types...>;





DESIGN_PATTERN_END
#endif // !_FACTORY_METHOD_HPP_

