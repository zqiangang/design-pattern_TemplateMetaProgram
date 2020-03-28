#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

template <typename container_object>
class default_iterator_hack_method
{
public:
	default_iterator_hack_method(): 
		_container_object(nullptr),
		_index(0)
	{}

	virtual void first(container_object * _con)
	{
		_container_object = _con;
	}

	virtual void next()
	{
		++_index;
	}
	virtual bool is_done()
	{
		if (_index >= _container_object->size())
			return true;
		return false;
	}
	/*virtual*/ typename container_object::value_type* current_element()
	{
		return _container_object->get(_index);
	}
private:
	size_t _index;
	container_object* _container_object;
};

template <typename container_object,
	template <typename> class hack_method = default_iterator_hack_method,
	template <typename> class ... minix_types>
class iterator_pattern_impl :
	public hack_method<container_object>,
	public sequence_template_inherit<iterator_pattern_impl<container_object,hack_method,minix_types...>,minix_types...>
{
	
};
DESIGN_PATTERN_END
#endif // !_ITERATOR_HPP_
