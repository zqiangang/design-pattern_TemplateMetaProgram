#ifndef _BRIDGE_HPP_
#define _BRIDGE_HPP_
#include "dp_tool_kits.hpp"
#include <iostream>
DESIGN_PATTERN_START

template <typename implementor_object, int bridge_count>
class default_bridge_hack_method
{
	static_assert(bridge_count > 0, "bridge count should greater zero");
public:
	default_bridge_hack_method() :
		_bridge_count(bridge_count),
		_implementors(new implementor_object* [bridge_count] {nullptr})
	{}

	void first()
	{
		for (int i = 0; i < _bridge_count; ++i)
			_implementors[i] = new implementor_object();
	}
	template <typename derived_impls, typename ... Args>
	void first(int idx, Args&& ... args)
	{
		if (idx >= _bridge_count)
			return;
		_implementors[idx] = new derived_impls(std::forward<Args>(args)...);
	}

	implementor_object* implementor(int idx)
	{
		if (idx >= _bridge_count || idx < 0)
			return nullptr;
		return _implementors[idx];
	}

	virtual ~default_bridge_hack_method()
	{
		for (int i = 0; i < _bridge_count; ++i)
		{
			if (_implementors[i] != nullptr)
				delete _implementors[i];
		}
	}

private:
	int _bridge_count;
	implementor_object** _implementors;
};

template <typename implementor_object>
class default_bridge_hack_method<implementor_object,1>
{
public:
	default_bridge_hack_method():
		_implementors(nullptr)
	{}

	void first()
	{
		if(_implementors == nullptr)
			_implementors = new implementor_object();
	}
	template <typename derived_impls, typename ... Args>
	void first(Args&& ... args)
	{
		if (_implementors != nullptr)
			delete _implementors;
		_implementors = new derived_impls(std::forward<Args>(args)...);
	}

	implementor_object* implementor()
	{
		return _implementors;
	}

	virtual ~default_bridge_hack_method()
	{
		if (_implementors != nullptr)
			delete _implementors;
	}

private:
	implementor_object* _implementors;
};

template <typename implementor_object,int bridge_count = 1,
	template <typename,int> class hack_method = default_bridge_hack_method>
class bridge_pattern_impl : public hack_method<implementor_object, bridge_count>
{
	static_assert(std::is_class_v<implementor_object>, "build_object is not an class type");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::is_polymorphic_v<implementor_object>, "implementor_object must be polymorphic");
#endif
};

DESIGN_PATTERN_END
#endif // !_BRIDGE_HPP_
