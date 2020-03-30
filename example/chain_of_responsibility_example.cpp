#include "../include/chain_of_responsibility.hpp"
USING_DESIGN_PATTERN;
#include <iostream>

// ���ȶ����Լ��� msg_type Ҳ����ʹ��Ĭ�ϵ� default_msg_type

class HelloMsg
{
public:
	virtual void hello()const
	{
		std::cout << "default print hello" << std::endl;
	}
};

// �¼�����
using myHMsg = event_type<HelloMsg, default_chain_of_responsibility_id<NilType>>;

class myHMsgConcreteA : public myHMsg
{
public:
	virtual void hello()const override
	{
		std::cout << "my hello world HMSG A" << std::endl;
	}
	virtual int id()const override			// �¼� id
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
	virtual int id()const override			// �¼� id
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
	virtual int id()const override			// �¼� id
	{
		return 3;
	}
};

// ��ͨ����	�� 
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

// ��Ա�������ڴ��������������ǻ��뷽��
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
	// ���ʵ��
	bool next_call()
	{
		if (as_dervied()->next_responsibility() == nullptr)
			return false;
		return next_handler(std::false_type);
	}
};




// ���,�����Լ��� ��Ϣ�������ʹ��Ĭ�ϵ� 
// ���� check_call �� my_chain_of_responsibility ��ü�� next_responsibility �Ƿ�Ϊ�յ�����
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
			std::cout << "HelloHandlerA ��ʼ���� msg" << std::endl;
			msg->hello();
			std::cout << "HelloHandlerA �������� msg" << std::endl;
			return true;
		}
		if (next_responsibility() == nullptr)
			return false;
		else
			return ::next_handler<my_chain_of_responsibility>(this,msg, std::false_type{});
	}

	virtual int id()const override				// ��ǰ�ദ�� id Ϊ 1�� �¼�
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
			std::cout << "HelloHandlerB ��ʼ���� msg" << std::endl;
			msg->hello();
			std::cout << "HelloHandlerB �������� msg" << std::endl;
			return true;
		}
		if (next_responsibility() == nullptr)
			return false;
		else
			return ::next_handler<my_chain_of_responsibility>(this,msg, std::false_type{});
	}

	virtual int id()const override				// ��ǰ�ദ�� id Ϊ 2 �� �¼�
	{
		return 2;
	}
};

//class HelloHandlerC : public HelloHandlerA
//{
//public:
//	// ֱ��ʹ�� HelloHandlerA �� handle ʵ��
//	//virtual bool handle(Msg_Type const* msg)override
//	//{
//	//	if (compare(this, msg))
//	//	{
//	//		std::cout << "HelloHandlerB ��ʼ���� msg" << std::endl;
//	//		msg->hello();
//	//		std::cout << "HelloHandlerB �������� msg" << std::endl;
//	//		return true;
//	//	}
//	//	next_responsibility()->handle(msg);
//	//}
//
//	virtual int id()const override				// ��ǰ�ദ�� id Ϊ 1�� �¼� ,���˴��� id 3
//	{
//		return 3;
//	}
//};

void test_chain_of_responsibility()
{
	// ����������
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
		std::cout << "�ɹ����� Msg A" << std::endl;
	}

	if (my_chain->handle(msgB))
	{
		std::cout << "�ɹ����� MsgB" << std::endl;
	}

	if (my_chain->handle(msgC))
	{
		std::cout << "�ɹ����� MsgC" << std::endl;
	}
	else
	{
		std::cout << "���˴��� MsgC" << std::endl;
	}
}