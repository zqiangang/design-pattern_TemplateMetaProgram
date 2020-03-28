#ifndef _CHAIN_OF_RESPONSIBILITY_HPP_
#define _CHAIN_OF_RESPONSIBILITY_HPP_
#include "dp_tool_kits.hpp"
#include "composite.hpp"
DESIGN_PATTERN_START

// 默认的 id 类
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
 *	作用 : 提供默认的 hack_method 方法, 如一些基本的通用操作等
 *  模板形参 : chain_of_responsibility , CRTP , 责任链的抽象基类
 *  模板形参 : identical , 为 hack_method 提供用户自定义的责任区别方法
 */
template <typename chain_of_responsibility,typename msg_type,typename identical>
class default_chain_of_responsibility_hack_method
{
public:
	using Chain_Of_Responsibility_Type = chain_of_responsibility;
	using Msg_Type = msg_type;
	using Identical_Type = identical;
public:
	// 默认构造函数
	// 初始化 _identical 和 _next_responsibility_node
	default_chain_of_responsibility_hack_method():
		_identical(new identical()),
		_next_responsibility_node(nullptr)
	{}
	// 初始化函数下一个的责任处理者,
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

	// 处理责任方法
	// 参数 : 所要处理的消息类型
	// 默认转发消息到下一个处理者,如果没有下一个处理者则返回 false ，不处理该消息
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


// 默认的责任链消息和处理者的匹配方法
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
