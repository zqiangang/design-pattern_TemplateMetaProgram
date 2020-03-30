#ifndef _DECORATOR_HPP_
#define _DECORATOR_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	���� : �ṩĬ�ϵ� hack_method ����, ��һЩ������ͨ�ò�����
 *  ģ���β� : component_object , װ�����Ļ���,�ͱ�װ�ε��๲ͬ����,��Ϊ default_decorator_hack_method
 *			 : �Ļ���
 */
template <typename component_object>
class default_decorator_hack_method : public component_object
{
public:
	default_decorator_hack_method()								// Ĭ�Ϲ��캯��,�� _component ��ʼ��Ϊ nullptr
		: _component(nullptr)
	{}

	template <typename concrete_component,typename ... Args>	// ��ʼ������,��ʼ����ǰװ����Ҫװ�εĶ���
	void first(Args&& ... args)
	{
		_component = new concrete_component(std::forward<Args>(args)...);
	}

	void first(component_object * object)
	{
		_component = object;
	}

	component_object* component()
	{
		return _component;
	}

	virtual ~default_decorator_hack_method()					// ��������,�� _component ��Ϊ nullptr ʱ,�ͷ� _component
	{
		if (_component != nullptr)
			delete _component;
	}
private:
	component_object* _component;
};

/*
 *	װ��ģʽ
 *	ģ���β� : component_object , װ�����Ļ���,�ͱ�װ�ε��๲ͬ����
 *  ģ��ģ���β� : hack_method , Ĭ�ϵ� hack_method ����,�����ṩһЩ�����Ĳ���,��� default_decorator_hack_method
 *  ����Լ�� : component_object Ӧ����һ�� class ����,�Ҳ�Ӧ��Ϊ empty class
 *	��		 : �� ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC ����ʽ,���ö�̬����Լ��
 */
template <typename component_object,
	template <typename> class hack_method = default_decorator_hack_method>
class decorator_pattern_impl : public hack_method<component_object>
{
	static_assert(std::is_class_v<component_object>, "component object must be a class type");
	static_assert(!std::is_empty_v<component_object>, "component object should is empty class");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::is_polymorphic_v<component_object>, "implementor_object must be polymorphic");
#endif
};

DESIGN_PATTERN_END
#endif // !_DECORATOR_HPP_
