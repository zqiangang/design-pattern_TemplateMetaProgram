#ifndef _MEDIATOR_HPP_
#define _MEDIATOR_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

template <typename ... minix_types>
class mediator_pattern_impl :
	public sequence_minixs_inherit<minix_types...>
{
	static_assert(std::conjunction_v<std::is_class<minix_types>...>, "all element type of minix_types ,must be is class type");
	static_assert(!std::conjunction_v<std::is_empty<minix_types>...>, "all element type of minix_types is empty class");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::disjunction_v<std::is_polymorphic<minix_types> ...>, "factory inherit all class element of minix_types,the result class must be polymorphic");
#endif
public:
	using result_type = mediator_pattern_impl<minix_types...>;
};

template <typename minix_type>
class mediator_pattern_impl<minix_type> : public minix_type
{
	static_assert(std::is_class_v<minix_type>, "minix_type should is a class type");
	static_assert(!std::is_empty_v<minix_type>, "minix_type should not be a empty class");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::is_polymorphic_v<minix_type>, "result class type must be polymorphic");
#endif
	using result_type = std::conditional_t<std::is_abstract_v<minix_type>, mediator_pattern_impl<minix_type>, minix_type>;
};


DESIGN_PATTERN_END
#endif // !_MEDIATOR_HPP_
