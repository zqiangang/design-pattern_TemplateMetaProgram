#ifndef _STATE_HPP_
#define _STATE_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START
/*
 *	״̬ģʽ 
 *  ģ���β�    : object ����,�ö�����е�ǰ״̬
 *  ģ��ģ���β� : ����Ҫ����ķ���������
 *  ���ͳ�Ա    : object ������
 *              : type , ��ǰ��ĵ�ʵ������
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
