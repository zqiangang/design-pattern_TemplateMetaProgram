#include "../include/flyweight.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

class flyweight_base
{
public:
	virtual void printMsg() = 0;
};

using myflyweight = flyweight_pattern_impl<flyweight_base>;

class character : public myflyweight
{
public:
	virtual void printMsg()override
	{
		std::cout << "character flyweight" << std::endl;
	}
};

class picture : public myflyweight
{
public:
	virtual void printMsg()override
	{
		std::cout << "picture flyweight" << std::endl;
	}
};

class digit : public myflyweight
{
public:
	virtual void printMsg()override
	{
		std::cout << "digit flyweight" << std::endl;
	}
};

enum flyweight_id : int
{
	character_id = 0,
	picture_id = 1,
	digit_id = 2
};

using myflyweight_factory = flyweight_factory_pattern_impl<myflyweight>;

void test_flyweight()
{
	myflyweight_factory mff;
	mff.first();
	auto res =  mff.get_shared_flyweight<digit>(flyweight_id::digit_id);
	res->printMsg();
	auto res1 = mff.get_shared_flyweight<picture>(flyweight_id::picture_id);
	auto res2 = mff.get_shared_flyweight<character>(flyweight_id::character_id);
	res1->printMsg();
	res2->printMsg();
}