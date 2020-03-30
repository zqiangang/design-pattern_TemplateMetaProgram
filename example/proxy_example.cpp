#include "../include/proxy.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

class subject
{
public:
	virtual void Op1() = 0;		// ������������
	virtual void Op2() = 0;		// ��������
};

using proxy_ob = proxy_pattern_impl<subject>;

class concrete1 : public subject
{
public:
	virtual void Op1()override
	{
		std::cout << "Op1 ������������" << std::endl;
	}

	virtual void Op2()override
	{
		std::cout << "Op2 ���������" << std::endl;
	}
};

class proxy_concrete1 : public proxy_ob
{
public:
	virtual void Op1()override			// ��ʱʵ���� vistual proxy
	{
		if (proxy_object() == nullptr)
			create<concrete1>();
		proxy_object()->Op1();
		std::cout << "vistual protected ��ʱʵ����" << std::endl;
	}

	virtual void Op2()override			// protected proxy
	{
		std::cout << "protected proxy ���� Op2 ���з���" << std::endl;
		return;		// ��������
	}
};

// remote proxy û�а���

void test_proxy()
{
	proxy_concrete1 p1;
	p1.Op1();
	p1.Op2();


	concrete1 c1;
	c1.Op1();
	c1.Op2();
}