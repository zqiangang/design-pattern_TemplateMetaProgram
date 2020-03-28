#include <iostream>
#include "../include/decorator.hpp"
USING_DESIGN_PATTERN;

class msg_base
{
public:
	virtual void printMsg() = 0;
};

using decorator_msg = decorator_pattern_impl<msg_base>;

class parentheses : public decorator_msg
{
public:
	virtual void printMsg()override
	{
		std::cout << "( ";
		component()->printMsg();
		std::cout << " )";
	}
};

class middle_bracket : public decorator_msg
{
public:
	virtual void printMsg()override
	{
		std::cout << "[ ";
		component()->printMsg();
		std::cout << " ]";
	}
};

class brace : public decorator_msg
{
public:
	virtual void printMsg()override
	{
		std::cout << "{ ";
		component()->printMsg();
		std::cout << " }";
	}
};

class hello_msg : public msg_base
{
public:
	virtual void printMsg()override
	{
		std::cout << "hello world";
	}
};

void test_decorator()
{
	brace br;
	middle_bracket mid;
	parentheses ph;
	br.first<hello_msg>();
	mid.first<brace>(br);
	ph.first<middle_bracket>(mid);

	br.printMsg();
	mid.printMsg();
	ph.printMsg();
}