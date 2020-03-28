#include "../include/prototype.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

// step 1		// 使用默认的 hack_method
// step 2

template <typename derived_type>
class minix1
{
public:
	using de_type = std::conditional_t<std::is_pointer_v<derived_type>, std::remove_cv_t<std::remove_pointer_t<derived_type>>, std::remove_cv_t<derived_type>>;
	using de_type_pointer = std::add_pointer_t<de_type>;
public:
	virtual de_type_pointer clone_msg()
	{
		std::cout << "print default message" << std::endl;
		return static_cast<typename derived_type::type_pointer>(this)->clone();
	}
};

// step 2
using prototype_base = design_pattern::prototype_pattern_impl<design_pattern::default_prototype_hack_method, minix1>;


class prototype1 : public prototype_base
{
public:
	virtual type_pointer clone()override
	{
		std::cout << "clone self" << std::endl;
		return new prototype1();
	}

	virtual type_pointer clone_msg()override
	{
		std::cout << "clone msg" << std::endl;
		return clone();
	}
};


void test_prototype()
{
	std::cout << "****************************** prototype ******************************" << std::endl;
	prototype1 pt1;

	prototype_base* pb = pt1.clone();

	prototype_base* pb2 = pt1.clone_msg();

	pb->clone();
	pb->clone_msg();


	delete pb;
	delete pb2;

	std::cout << "****************************** prototype ******************************" << std::endl;
}