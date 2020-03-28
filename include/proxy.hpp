#ifndef _PROXY_HPP_
#define _PROXY_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	作用 : 提供默认的 hack_method 方法, 如一些基本的通用操作等
 *  模板形参 : subject , 代理类的基类,和被代理类的共同基类,作为 default_proxy_hack_method
 *			 : 的基类
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
 *  代理模式
 *  模板形参 : subject , 代理模式的基类,用以存储代理的实体对象
 *  模板模板形参 : hack_method , 默认提供的一些公共方法 
 *  断言约束 : subject 应当是 class 类型, 且不应当为空
 *  宏       : 如果定义 ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC ,开启 多态断言检查
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
