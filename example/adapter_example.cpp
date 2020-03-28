#include "../include/adapter.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

class hello_impl
{
public:
	void hello()
	{
		std::cout << "hello";
	}

	void world()
	{
		std::cout << "world";
	}
};

class termi_impl
{
public:
	void space()const
	{
		std::cout << " ";
	}

	void next_line()const
	{
		std::cout << "\n";
	}

	void end()const
	{
		std::cout << ".";
	}
};

class  say
{
public:
	virtual void say_hello_world() = 0;
};

class sound
{
public:
	virtual void say_sound()
	{
		std::cout << "声音很好听" << std::endl;
	}
};



using adapter_txt_say = design_pattern::adapter_pattern_impl<design_pattern::adaptee_box<hello_impl, termi_impl>, design_pattern::default_adapter_hack_method, translate_simple_tt<say,sound>::result_type>;

class txt_say_imple : public adapter_txt_say
{
public:
	virtual void say_hello_world()override
	{
		std::cout << "adapter 实现接口" << std::endl;
		first();		// 首先,调用 first 初始化 
		adaptee<hello_impl>()->hello();
		adaptee<termi_impl>()->space();
		adaptee<hello_impl>()->world();
		adaptee<termi_impl>()->end();
		adaptee<termi_impl>()->next_line();
		std::cout << "完成" << std::endl;
	}

	virtual void say_sound()override
	{
		std::cout << "嗓门很大" << std::endl;
	}
};

void test_adapter()
{
	std::cout << "****************************** adapter ******************************" << std::endl;

	txt_say_imple txt;
	txt.say_hello_world();
	txt.say_sound();

	std::cout << "****************************** adapter ******************************" << std::endl;
}