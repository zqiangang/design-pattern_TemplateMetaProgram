#ifndef _SEQUENCE_MINIX_HPP_
#define _SEQUENCE_MINIX_HPP_
#include "dp_macro.hpp"
#include "helper_template_kit.hpp"

DESIGN_PATTERN_START

// ���еĲ���������Ӧ���Ƕ�̬��
template <typename ... minix_types>
class sequence_minixs_inherit;

template <typename ... minix_types>
class sequence_minixs_inherit : public minix_types...
{
	//static_assert()
};

template <>
class sequence_minixs_inherit<>
{};

template <typename T,
	template <typename> class ... template_paras>
class sequence_template_inherit : public template_paras<T>...
{

};



DESIGN_PATTERN_END

#endif // !_SEQUENCE_MINIX_HPP_
