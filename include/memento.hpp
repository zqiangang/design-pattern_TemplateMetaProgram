#ifndef _MEMENTO_HPP_
#define _MEMENTO_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

template <typename data_type>
class default_memento_hack_method
{
public:
	virtual data_type* get_state() = 0;
	virtual void set_state(data_type*) = 0;
};

template <typename data_type,
	template <typename> class hack_method = default_memento_hack_method,
	template <typename> class ... minix_types>
class memento_pattern_impl :
	public hack_method<data_type>,
	public sequence_template_inherit<memento_pattern_impl<data_type,hack_method,minix_types...>,minix_types...>
{

};
DESIGN_PATTERN_END
#endif // !_MEMENTO_HPP_
