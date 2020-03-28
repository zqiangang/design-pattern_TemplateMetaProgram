#include "../include/abstract_factory.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

// step.1

class myminix
{
public:
	virtual void page() = 0;
	virtual void count()
	{
		std::cout << "默认计数" << std::endl;
	}

	virtual void name()
	{
		std::cout << "计数工具" << std::endl;
	}
};


// step.2
using my_abs_fac = design_pattern::abstract_factory_pattern_impl<myminix>;

// step.3 使用

class c1 : public my_abs_fac
{
public:
	virtual void page()override
	{
		std::cout << "C1 的 page" << std::endl;
	}

	virtual void count() override
	{
		std::cout << "C1 的 count" << std::endl;
	}
};

class c2 : public my_abs_fac
{
public:
	virtual void page()override
	{
		std::cout << "C2 的 page" << std::endl;
	}

	virtual void count() override
	{
		std::cout << "C2 的 count" << std::endl;
	}
};

void test_abstract_factory()
{
	std::cout << "******************************abstract factory******************************" << std::endl;
	my_abs_fac* m = new c1();
	m->page();
	m->count();
	m->name();

	delete m;

	m = new c2();
	m->page();
	m->count();
	m->name();

	delete m;
	std::cout << "******************************abstract factory******************************" << std::endl;
}