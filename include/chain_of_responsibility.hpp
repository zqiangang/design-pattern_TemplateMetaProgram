#ifndef _CHAIN_OF_RESPONSIBILITY_HPP_
#define _CHAIN_OF_RESPONSIBILITY_HPP_
#include "dp_tool_kits.hpp"
#include "composite.hpp"
DESIGN_PATTERN_START

// Ĭ�ϵ� id ��
template <typename>
class default_chain_of_responsibility_id
{
public:
	virtual int id() const= 0;
};

template <typename ... minix_types>
using event_type = composite_pattern_impl<minix_types...>;

using default_msg_type = event_type<default_chain_of_responsibility_id<NilType>>;

/*
 *	���� : �ṩĬ�ϵ� hack_method ����, ��һЩ������ͨ�ò�����
 *  ģ���β� : chain_of_responsibility , CRTP , �������ĳ������
 *  ģ���β� : identical , Ϊ hack_method �ṩ�û��Զ�����������𷽷�
 */
template <typename chain_of_responsibility,typename msg_type,typename identical>
class default_chain_of_responsibility_hack_method
{
public:
	using Chain_Of_Responsibility_Type = chain_of_responsibility;
	using Msg_Type = msg_type;
	using Identical_Type = identical;
public:
	// Ĭ�Ϲ��캯��
	// ��ʼ�� _identical �� _next_responsibility_node
	default_chain_of_responsibility_hack_method():
		_identical(new identical()),
		_next_responsibility_node(nullptr)
	{}
	// ��ʼ��������һ�������δ�����,
	template <typename Next_Responsibility,typename ... Args>
	void first(Args && ... args)
	{
		if (_next_responsibility_node != nullptr)
			delete _next_responsibility_node;
		_next_responsibility_node = new Next_Responsibility(std::forward<Args>(args)...);
	}

	void first(Chain_Of_Responsibility_Type * chain_node)
	{
		if (_next_responsibility_node != nullptr)
			delete _next_responsibility_node;
		_next_responsibility_node = chain_node;
	}

	// �������η���
	// ���� : ��Ҫ�������Ϣ����
	// Ĭ��ת����Ϣ����һ��������,���û����һ���������򷵻� false �����������Ϣ
	virtual bool handle(Msg_Type const* msg)
	{
		if (_next_responsibility_node == nullptr)
			return false;
		return _next_responsibility_node->handle(msg);
	}

	Chain_Of_Responsibility_Type* next_responsibility()
	{
		return _next_responsibility_node;
	}

	~default_chain_of_responsibility_hack_method()
	{
		if (_next_responsibility_node != nullptr)
			delete _next_responsibility_node;
	}
protected:
	bool compare(Chain_Of_Responsibility_Type const* handler, Msg_Type const* msg)
	{
		return _identical->equal(handler, msg);
	}
private:
	identical* _identical;
	chain_of_responsibility* _next_responsibility_node;
};


// Ĭ�ϵ���������Ϣ�ʹ����ߵ�ƥ�䷽��
class default_chain_of_responsibility_identical
{
public:
	template<typename chain_of_responsibility,typename msg_type>
	bool equal(chain_of_responsibility* responsibility, msg_type* msg)
	{
		return responsibility->id() == msg->id();
	}
};

template<typename msg_type,typename identical,
	template <typename,typename,typename> class hack_method = default_chain_of_responsibility_hack_method,
	template <typename> class ... minix_types>
class chain_of_responsibility_pattern_impl :
	public hack_method<chain_of_responsibility_pattern_impl<msg_type, identical, hack_method, minix_types...>,msg_type,identical>,
	public sequence_template_inherit<chain_of_responsibility_pattern_impl<msg_type, identical, hack_method, minix_types...>, minix_types...>
{
	
};

using default_chain_of_responsibility_pattern_impl = chain_of_responsibility_pattern_impl<
	default_msg_type,
	default_chain_of_responsibility_identical,
	default_chain_of_responsibility_hack_method,
	default_chain_of_responsibility_id>;


DESIGN_PATTERN_END
#endif // !_CHAIN_OF_RESPONSIBILITY_HPP_
