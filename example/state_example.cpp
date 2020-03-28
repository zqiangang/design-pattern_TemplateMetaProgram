#include "../include/state.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

class cat;

template <typename object,typename derived_type,typename...>
class abs_state
{
public:
	virtual void eat(object*) = 0;

	virtual void state(object*) = 0;

protected:
	virtual void change_state(object*o, derived_type*d)
	{
		o->change_state(d);
	}
};

using cat_state = state_pattern_impl<cat, abs_state>;

class full_state : public cat_state
{
public:
	virtual void eat(object_type* o)
	{
		std::cout << "好饱， 不吃了"  << std::endl;
	}

	virtual void state(object_type*)
	{
		std::cout << "悠闲散步中" << std::endl;
	}
};

class hungry_cat : public cat_state
{
public:
	virtual void eat(object_type*o)
	{
		std::cout << "吃饭中...." << std::endl;
		change_state(o, new full_state());
	}

	virtual void state(object_type*)
	{
		std::cout << "好饿 , 想吃饭" << std::endl;
	}
};

class cat
{
public:
	cat(cat_state * cst = nullptr)
		: cstate(cst)
	{}

	void eat()
	{
		cstate->eat(this);
	}

	void state()
	{
		cstate->state(this);
	}

protected:
	void change_state(cat_state * cs)
	{
		if (cstate != nullptr)
			delete cstate;
		cstate = cs;
	}
private:
	friend class abs_state<cat, state_pattern_impl<cat, abs_state>>;

	cat_state* cstate;
};

void test_state()
{
	cat c(new hungry_cat());
	c.eat();
	c.state();
	c.eat();
	c.state();
}