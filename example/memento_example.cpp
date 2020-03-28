#include "../include/memento.hpp"
USING_DESIGN_PATTERN;
#include <iostream>

// 备忘录模式

template <typename derived_type>
class minix_as_flink_node			// 单向链 ->a->b 新加入的为首节点
{
public:
	minix_as_flink_node():
		_up_node(nullptr),
		_next_node(nullptr)
	{}

	void set_up_node(derived_type* up_nd)
	{
		_up_node = up_nd;
	}

	void set_next_node(derived_type* nx_nd)
	{
		_next_node = nx_nd;
	}

	derived_type* up_node()
	{
		return _up_node;
	}

	derived_type* next_node()
	{
		return _next_node;
	}
private:
	derived_type* _up_node;
	derived_type* _next_node;
};

struct pdata_type
{
	int age;
	char const* name;
};

using my_memento = memento_pattern_impl<pdata_type, default_memento_hack_method, minix_as_flink_node>;

class concrete_memento : public my_memento
{
public:
	concrete_memento()
		:pd(nullptr)
	{}

	virtual pdata_type* get_state()override
	{
		return pd;
	}
	virtual void set_state(pdata_type * _pd) override
	{
		pd = _pd;
	}
private:
	pdata_type* pd;
};


class people
{
public:
	people(char const* name,int age): 
		memento(nullptr),
		_people(new pdata_type{age,name})
	{}

	void change_name(const char* name)
	{
		create_memento();
		memento->set_state(_people);
		_people = new pdata_type{ _people->age,name };

	}

	void undo()
	{
		if (memento == nullptr)
			return;
		if (memento->next_node() == nullptr)
		{
			create_memento();
			memento->set_state(_people);
			memento = memento->up_node();
		}

		_people = memento->get_state();
		if(memento->up_node())				// 检查是否临街
			memento = memento->up_node();
	}

	void redo()
	{
		if (memento == nullptr)
			return;
		_people = memento->get_state();
		if(memento->next_node())			// 检查是否临街
			memento = memento->next_node();
	}

	void show()
	{
		std::cout << "name : " << _people->name << " " << "age : " << _people->age << std::endl;
	}
protected:
	void create_memento()
	{
		if (memento == nullptr)
		{
			memento = new concrete_memento();
			return;
		}
		my_memento* tmp = new concrete_memento();
		tmp->set_up_node(memento);
		memento->set_next_node(tmp);
		memento = tmp;
	}

private:
	my_memento* memento;
	pdata_type* _people;
};

void test_memento()
{
	people p("qiangang", 22);
	p.show();
	p.change_name("zhangang");
	p.show();
	p.change_name("hep");
	p.show();

	std::cout << "取消操作" << std::endl;
	p.undo();
	p.show();
	p.undo();
	p.show();

	std::cout << "重新操作" << std::endl;
	p.redo();
	p.show();
	p.redo();
	p.show();
	p.redo();
	p.show();
}