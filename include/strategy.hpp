#ifndef _STRATEGY_HPP_
#define _STRATEGY_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	���� : �ṩһЩĬ�ϵķ��������ݳ�Ա
 *  ģ���β� : context , ʹ�ò��Զ���������Ķ���
*/
template <typename context>
class default_strategy_hack_method
{
public:
	virtual void first(context* ctxt)
	{
		_context = ctxt;
	}
	virtual void compose() = 0;
	virtual ~default_strategy_hack_method(){}
protected:
	virtual context*& get_context()
	{
		return _context;
	}
private:
	context* _context;
};

/*
 *	����ģʽ
 *	ģ���β� : context , �����Ķ�������
 *	ģ��ģ���β� : hack_method , �ṩһЩĬ�ϵķ��������ݳ�Ա
 *  ģ��ģ���β��� : �ṩ�û�������ķ��������ݳ�Ա
 *  ����Լ�� : context , Ӧ����һ�� class ����
*/
template <typename context,
	template <typename> class hack_method = default_strategy_hack_method,
	template <typename> class ... minix_types>
class strategy_pattern_impl :
	public hack_method<context>,
	public sequence_template_inherit<strategy_pattern_impl<context,hack_method,minix_types...>,minix_types...>
{
	static_assert(std::is_class_v<context>, "context should is an class type");
};

DESIGN_PATTERN_END
#endif // !_STRATEGY_HPP_
