#ifndef _PROXY_HPP_
#define _PROXY_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	���� : �ṩĬ�ϵ� hack_method ����, ��һЩ������ͨ�ò�����
 *  ģ���β� : subject , ������Ļ���,�ͱ�������Ĺ�ͬ����,��Ϊ default_proxy_hack_method
 *			 : �Ļ���
 */
template <typename subject>
class default_proxy_hack_method : public subject
{
public:
    default_proxy_hack_method():
        _proxy_object(nullptr)
    {}
protected:
    subject* proxy_object()const
    {
        return _proxy_object;
    }
    template <typename proxy_type,typename ... Args>
    void create(Args&& ... args)
    {
        _proxy_object = new proxy_type(std::forward<Args>(args)...);
    }

private:
    subject* _proxy_object;
};

/*
 *  ����ģʽ
 *  ģ���β� : subject , ����ģʽ�Ļ���,���Դ洢�����ʵ�����
 *  ģ��ģ���β� : hack_method , Ĭ���ṩ��һЩ�������� 
 *  ����Լ�� : subject Ӧ���� class ����, �Ҳ�Ӧ��Ϊ��
 *  ��       : ������� ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC ,���� ��̬���Լ��
 */
template <typename subject,
    template <typename> class hack_method = default_proxy_hack_method>
class proxy_pattern_impl : public hack_method<subject>
{
    static_assert(std::is_class_v<subject>, "subject must be a class type");
    static_assert(!std::is_empty_v<subject>, "subject should is empty class");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
    static_assert(std::is_polymorphic_v<subject>, "subject must be polymorphic");
#endif
};


DESIGN_PATTERN_END
#endif // !_PROXY_HPP_
