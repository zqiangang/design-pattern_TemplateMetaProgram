#ifndef _STATE_HPP_
#define _STATE_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START
/*
 *	状态模式 
 *  模板形参    : object 对象,该对象持有当前状态
 *  模板模板形参 : 用想要混入的方法的数据
 *  类型成员    : object 的类型
 *              : type , 当前类的的实体类型
*/
template <typename object, template <typename,typename> class ... minix_types>
class state_pattern_impl :
	public minix_types<object,state_pattern_impl<object, minix_types...>>...
{
public:
    using object_type = object;
    using type = state_pattern_impl<object, minix_types...>;
    
};

DESIGN_PATTERN_END
#endif // !_STATE_HPP_
