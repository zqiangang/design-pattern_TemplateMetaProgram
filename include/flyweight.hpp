#ifndef _FLYWEIGHT_HPP_
#define _FLYWEIGHT_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	��Ԫģʽʵ��
 *  ģ���β��� : flyweight_minix , ���� ��Ԫ������Ҫ����ķ��������ݳ�Ա��
 *  ����Լ�� : flyweight_minix �Ļ������Ӧ���� class ����
 *			 : ��������� ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC ,��ô flyweight_minix �����ٴ���һ��Ԫ���� ��̬�� 
 *	��Ա���� : result_type ���� flyweight_minix ��õ��Ľ������ 
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
 *  ��Ԫģʽ�ػ�
 *	ģ���β� : flyweight_object ,���������,�������ṩ�����ͳ�Ա
 *  ����Լ�� : flyweight_object ,Ӧ����һ�� class ����
 *			 : ������� ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC , ��ô flyweight_object Ӧ���Ƕ�̬��
 *  ��Ա���� : result_type , ��� flyweight_object ��ô result_type ���� flyweight_pattern_impl<flyweight_object>
 *			 : ���� result_type Ϊ flyweight_object ģ���β�����
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
 *	���� : �ṩĬ�ϵ� hack_method ����, ��һЩ������ͨ�ò�����
 *  ģ���β� : flyweight , ��Ԫ����
 *  �����β� : flyweight_count , �ڲ��洢�������Ԫ��������
 */
template <typename flyweight, int flyweight_count>
class default_flyweight_factory_hack_method
{
public:
	default_flyweight_factory_hack_method() :								// Ĭ�Ϲ��캯��,��ʼ�� _flyweight_objects Ϊ nullptr
		_flyweight_objects(nullptr)
	{}

	virtual void first()													// ��ʼ������,��ʼ�� _flyweight_object Ϊ flyweight_count ����������
	{
		if (_flyweight_objects == nullptr)
			_flyweight_objects = new flyweight*[flyweight_count]{ nullptr };
	}
	
	template<typename share_flyweight, typename Key, typename ...Args>		// ��ȡ��Ԫ����ͨ�� key ֵ,�������򴴽������뵽_flyweight_objects
	flyweight * get_shared_flyweight(Key const& key, Args&& ... args)
	{
		if (!_flyweight_objects[key])
			_flyweight_objects[key] = new share_flyweight(std::forward<Args>(args)...);
		return _flyweight_objects[key];
	}

	template <typename non_share_flyweight,typename ... Args>
	flyweight* create_non_shared_flyweight(Args && ... args)const			// ������Ԫ�����еķǹ�����
	{
		return new non_share_flyweight(std::forward<Args>(args)...);
	}

private:
	flyweight** _flyweight_objects;
};

/*
 *	��Ԫ����
 *	ģ���β� : flyweight , ��Ԫ�������,���û���Զ������һ���� flyweight_pattern_impl,��� flyweight_pattern_impl
 *  �����β� : flyweight_count , ָ�� default_flyweight_factory_hack_method,�ڲ����洢����Ԫ��������
 *  ģ��ģ���β� : hack_method , Ĭ���ṩ��һЩ��Ԫ�����Ļ�������,�����Զ����Լ��� hack_method ,��Ҫ����ģ���β�Լ��
 *				 : minix_types , һЩ�û���Ҫ�Ĳ���,ͨ����ģ���βλ��� flyweight_factory ,���뷽����������
 *  ����Լ�� : flyweight_count ��Ӧ��С�ڵ��� 0
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
