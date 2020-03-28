#include "../include/proxy.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

class subject
{
public:
	virtual void Op1() = 0;		// 代理正常访问
	virtual void Op2() = 0;		// 代理保护，
};

using proxy_ob = proxy_pattern_impl<subject>;

class concrete1 : public subject
{
public:
	virtual void Op1()override
	{
		std::cout << "Op1 代理正常访问" << std::endl;
	}

	virtual void Op2()override
	{
		std::cout << "Op2 代理不会访问" << std::endl;
	}
};

class proxy_concrete1 : public proxy_ob
{
public:
	virtual void Op1()override			// 用时实例化 vistual proxy
	{
		if (proxy_object() == nullptr)
			create<concrete1>();
		proxy_object()->Op1();
		std::cout << "vistual protected 用时实例化" << std::endl;
	}

	virtual void Op2()override			// protected proxy
	{
		std::cout << "protected proxy 不对 Op2 进行访问" << std::endl;
		return;		// 代理不访问
	}
};

// remote proxy 没有案例

void test_proxy()
{
	proxy_concrete1 p1;
	p1.Op1();
	p1.Op2();


	concrete1 c1;
	c1.Op1();
	c1.Op2();
}