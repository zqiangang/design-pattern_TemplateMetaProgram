#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	���ģʽ
 *  ģ���β� : minix_types , ��Ҫ������Ļ�����,�����ṩ�ӿڷ���
 *  ����Լ�� : ���еĻ�����,Ӧ������ class ����
 *  ��       : �� ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC ����ʽ,���ö�̬����Լ��
 *  ��Ա���� : result_type ���ص���ϵĽ������
 */
template <typename ... minix_types>
class _composite_pattern_impl : public sequence_minixs_inherit<minix_types...>
{
	static_assert(std::conjunction_v<std::is_class<minix_types>...>, "found element type of minix_type has an non class type");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::disjunction_v<std::is_polymorphic<minix_types>...>, "factory inherit all class element of minix_types,the result class must be polymorphic");
#endif
public:
	using result_type = _composite_pattern_impl<minix_types...>;
};

/*
 *  ���ģʽ�ػ�, ������һ��������ʱ
 *  ����Լ�� : ������Ӧ���� class ����
 *  ��       : �� ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC ����ʽ,���ö�̬����Լ��
 *  ��Ա���� : result_type ���ص���ϵĽ������
 */
template <typename minix_type>
class _composite_pattern_impl<minix_type> : public minix_type
{
	static_assert(std::is_class_v<minix_type>, "found element type of minix_type has an non class type");
#if defined(ALL_PATTERN_RESULT_MUST_BE_POLYMORPGIC)
	static_assert(std::is_polymorphic_v<minix_type>, "factory inherit all class element of minix_types,the result class must be polymorphic");
#endif
public:
	using result_type = std::conditional_t<std::is_abstract_v<minix_type>, _composite_pattern_impl<minix_type>, minix_type>;
};


/*
 *	���ģʽ����
 *	ģ���β��� : minix_types ,��Ҫ������Ľӿ���
 */
template <typename ... minix_types>
using composite_pattern_impl = typename _composite_pattern_impl<minix_types...>::result_type;

DESIGN_PATTERN_END