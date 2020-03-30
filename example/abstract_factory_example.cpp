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
		std::cout << "Ĭ�ϼ���" << std::endl;
	}

	virtual void name()
	{
		std::cout << "��������" << std::endl;
	}
};


// step.2
using my_abs_fac = design_pattern::abstract_factory_pattern_impl<myminix>;

// step.3 ʹ��

class c1 : public my_abs_fac
{
public:
	virtual void page()override
	{
		std::cout << "C1 �� page" << std::endl;
	}

	virtual void count() override
	{
		std::cout << "C1 �� count" << std::endl;
	}
};

class c2 : public my_abs_fac
{
public:
	virtual void page()override
	{
		std::cout << "C2 �� page" << std::endl;
	}

	virtual void count() override
	{
		std::cout << "C2 �� count" << std::endl;
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