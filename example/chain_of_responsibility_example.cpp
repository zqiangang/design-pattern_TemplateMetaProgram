#include "../include/chain_of_responsibility.hpp"
USING_DESIGN_PATTERN;
#include <iostream>

// 首先定义自己的 msg_type 也可以使用默认的 default_msg_type

class HelloMsg
{
public:
	virtual void hello()const
	{
		std::cout << "default print hello" << std::endl;
	}
};

// 事件类型
using myHMsg = event_type<HelloMsg, default_chain_of_responsibility_id<NilType>>;

class myHMsgConcreteA : public myHMsg
{
public:
	virtual void hello()const override
	{
		std::cout << "my hello world HMSG A" << std::endl;
	}
	virtual int id()const override			// 事件 id
	{
		return 1;
	}
};

class myHMsgConcreteB : public myHMsg
{
public:
	virtual void hello()const override
	{
		std::cout << "my hello world HMSG B" << std::endl;
	}
	virtual int id()const override			// 事件 id
	{
		return 2;
	}
};

class myHMsgConcreteC : public myHMsg
{
public:
	virtual void hello()const override
	{
		std::cout << "my hello world HMSG C" << std::endl;
	}
	virtual int id()const override			// 事件 id
	{
		return 3;
	}
};

// 普通函数	或 
template <typename handler,typename msg_type>
bool next_handler(handler* hp, msg_type const *,std::true_type is_null_handler)
{
	return false;
}

template <typename handler, typename msg_type>
bool next_handler(handler* hp, msg_type const * msg,std::false_type is_null_handler)
{
	return hp->next_responsibility()->handle(msg);
}

// 成员函数，在创建责任链类型是混入方法
template <typename dervied_type>
class check_call
{
private:
	// CRTP
	dervied_type* as_dervied()
	{
		return static_cast<dervied_type*>(this);
	}
	dervied_type const* as_dervied()const
	{
		return static_cast<dervied_type const*>(this);
	}

	bool next_handler(std::false_type is_null_handler)
	{
		return as_dervied()->next_responsibility()->next_responsibility();
	}
public:
	// 便捷实现
	bool next_call()
	{
		if (as_dervied()->next_responsibility() == nullptr)
			return false;
		return next_handler(std::false_type);
	}
};




// 其次,定义自己的 消息处理类或使用默认的 
// 混入 check_call 令 my_chain_of_responsibility 获得检查 next_responsibility 是否为空的能力
using my_chain_of_responsibility = chain_of_responsibility_pattern_impl<
	myHMsg, 
	default_chain_of_responsibility_identical,
	default_chain_of_responsibility_hack_method,
	default_chain_of_responsibility_id,
	/*check_call */>;	

class HelloHandlerA : public my_chain_of_responsibility
{
public:
	virtual bool handle(Msg_Type const* msg)override
	{
		if (compare(this, msg))
		{
			std::cout << "HelloHandlerA 开始处理 msg" << std::endl;
			msg->hello();
			std::cout << "HelloHandlerA 结束处理 msg" << std::endl;
			return true;
		}
		if (next_responsibility() == nullptr)
			return false;
		else
			return ::next_handler<my_chain_of_responsibility>(this,msg, std::false_type{});
	}

	virtual int id()const override				// 当前类处理 id 为 1的 事件
	{
		return 1;
	}
};

class HelloHandlerB : public my_chain_of_responsibility
{
public:
	virtual bool handle(Msg_Type const* msg)override
	{
		if (compare(this, msg))
		{
			std::cout << "HelloHandlerB 开始处理 msg" << std::endl;
			msg->hello();
			std::cout << "HelloHandlerB 结束处理 msg" << std::endl;
			return true;
		}
		if (next_responsibility() == nullptr)
			return false;
		else
			return ::next_handler<my_chain_of_responsibility>(this,msg, std::false_type{});
	}

	virtual int id()const override				// 当前类处理 id 为 2 的 事件
	{
		return 2;
	}
};

//class HelloHandlerC : public HelloHandlerA
//{
//public:
//	// 直接使用 HelloHandlerA 的 handle 实现
//	//virtual bool handle(Msg_Type const* msg)override
//	//{
//	//	if (compare(this, msg))
//	//	{
//	//		std::cout << "HelloHandlerB 开始处理 msg" << std::endl;
//	//		msg->hello();
//	//		std::cout << "HelloHandlerB 结束处理 msg" << std::endl;
//	//		return true;
//	//	}
//	//	next_responsibility()->handle(msg);
//	//}
//
//	virtual int id()const override				// 当前类处理 id 为 1的 事件 ,无人处理 id 3
//	{
//		return 3;
//	}
//};

void test_chain_of_responsibility()
{
	// 创建责任连
	my_chain_of_responsibility* my_chain = new HelloHandlerA();
	my_chain_of_responsibility* my_nodeB = new HelloHandlerB();
	//my_chain_of_responsibility* my_nodeC = new HelloHandlerC();

	//my_nodeB->first(my_nodeC);
	my_chain->first(my_nodeB);

	myHMsg* msgA = new myHMsgConcreteA();
	myHMsg* msgB = new myHMsgConcreteB();
	myHMsg* msgC = new myHMsgConcreteC();

	if (my_chain->handle(msgA))
	{
		std::cout << "成功处理 Msg A" << std::endl;
	}

	if (my_chain->handle(msgB))
	{
		std::cout << "成功处理 MsgB" << std::endl;
	}

	if (my_chain->handle(msgC))
	{
		std::cout << "成功处理 MsgC" << std::endl;
	}
	else
	{
		std::cout << "无人处理 MsgC" << std::endl;
	}
}