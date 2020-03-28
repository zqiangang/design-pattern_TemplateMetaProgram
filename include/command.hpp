#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

template <typename  derived_type>
class default_command_hack_method
{
public:
	virtual void execute() = 0;
	virtual void first()
	{}
};

template <typename derived_type>
class default_command_minix_type
{

public:
	virtual void discard() = 0;
};

template <template <typename> class hack_method = default_command_hack_method,
	template <typename> class ... minix_types>
class command_pattern_impl : 
	public hack_method<command_pattern_impl<hack_method>>,
	public sequence_template_inherit<command_pattern_impl<hack_method,minix_types...>,minix_types...>
{
public:
	virtual ~command_pattern_impl(){}
};

DESIGN_PATTERN_END
#endif // !_COMMAND_HPP_
