#include "../include/command.hpp"
#include <iostream>
#include <list>
USING_DESIGN_PATTERN;


class hello
{
public:
	void printHello()const
	{
		std::cout << "Hello" << std::endl;
	}
};

class world
{
public:
	void printWorld()const
	{
		std::cout << "World" << std::endl;
	}
};

class space
{
public:
	void printSpace()const
	{
		std::cout << " " << std::endl;
	}
};

using my_command_base = command_pattern_impl<default_command_hack_method, default_command_minix_type>;

class command_hello : public my_command_base
{
public:
	virtual void first()override
	{
		_hello = new hello();
	}

	virtual void execute()override
	{
		std::cout << "ִ������" << std::endl;
		_hello->printHello();
	}

	virtual void discard()override
	{
		std::cout << "ȡ�� printHello ����" << std::endl;
	}

private:
	hello* _hello;
};


class command_world : public my_command_base
{
public:
	virtual void first()override
	{
		_world = new world();
	}

	virtual void execute()override
	{
		std::cout << "ִ������" << std::endl;
		_world->printWorld();
	}

	virtual void discard()override
	{
		std::cout << "ȡ�� printWorld ����" << std::endl;
	}

private:
	world* _world;
};


class command_space : public my_command_base
{
public:
	virtual void first()override
	{
		_space = new space();
	}

	virtual void execute()override
	{
		std::cout << "ִ������" << std::endl;
		_space->printSpace();
	}

	virtual void discard()override
	{
		std::cout << "ȡ�� printSpace ����" << std::endl;
	}

private:
	space* _space;
};


class command_macro : public my_command_base
{
public:
	virtual void first()override
	{
		_hello = new hello();
		_world = new world();
		_space = new space();
	}

	virtual void execute()override
	{
		std::cout << "ִ������" << std::endl;
		_hello->printHello();
		_world->printWorld();
		_space->printSpace();
	}

	virtual void discard()override
	{
		std::cout << "ȡ�� printHello ����" << std::endl;
		std::cout << "ȡ�� printWorld ����" << std::endl;
		std::cout << "ȡ�� printSpace ����" << std::endl;
	}

	virtual ~command_macro()
	{

	}
private:
	hello* _hello;
	world* _world;
	space* _space;
};

class button_hello_world
{
public:
	button_hello_world()
		: cma(new command_macro())
	{}

	void Click()
	{
		std::cout << "��� hello world��ť" << std::endl;
		cma->execute();
	}
private:
	my_command_base* cma;
};

void test_command()
{
	button_hello_world bhw;
	bhw.Click();
	
}