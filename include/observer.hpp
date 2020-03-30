#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	���� : hack_method ����
 *	�ṩһЩ�����ķ���
 */
template<typename observer_object>
class default_observer_subject_hack_method
{
public:
	virtual void add_observer(observer_object* observer) = 0;
	virtual void remove_observer(observer_object* observer) = 0;
	virtual void notify()const = 0;
};

/*
 *	�۲���ģʽ ���۲���
 *  ģ���β� : observer_object , �۲��߶���Ļ���
 *	ģ��ģ���β� : �ṩһЩ�����ķ���
 *	ģ��ģ���β��б� : �ṩһЩ�û��Զ���ķ���
 */
template <typename observer_object,
	template <typename> class hack_method = default_observer_subject_hack_method,
	template <typename> class ... minix_types>
class observer_patterm_subject_impl :
	public hack_method<observer_object> ,
	public sequence_template_inherit<
	observer_patterm_subject_impl<observer_object, hack_method, minix_types...>, minix_types...>
{
	static_assert(std::is_class_v<observer_object>, "observer object must be class type");
};

/*
 *	���� : �ṩһЩ�����Ĺ۲��߷���
 */
template <typename subject_object>
class default_observer_observer_hack_method
{
public:
	virtual void update(const subject_object*) = 0;
};

/*
 *	�۲���ģʽ �۲���
 *  ģ���β� : subject_object ���۲��ߵĻ���
 *	ģ��ģ���β� : �ṩһЩ�����Ĺ۲��߷���
 *  ģ��ģ���β��б� : �ṩһЩ�û��Զ���ķ���
*/
template <typename subject_object,
	template <typename> class hack_method = default_observer_observer_hack_method,
	template <typename> class ... minix_types>
class observer_pattern_observer_impl : 
    public hack_method<subject_object>,
    public sequence_template_inherit<
        observer_pattern_observer_impl<subject_object,hack_method,minix_types...>,minix_types...>
{
	static_assert(std::is_class_v<subject_object>, "subiect object must be class type");
};

DESIGN_PATTERN_END
#endif // !_OBSERVER_HPP_
