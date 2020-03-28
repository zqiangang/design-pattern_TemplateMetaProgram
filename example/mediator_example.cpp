#include "../include/mediator.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

class mediator_minix
{
public:
	virtual void eat_event() = 0;
	virtual void hit_event() = 0;
};

using mediator_base = mediator_pattern_impl<mediator_minix>;


class base
{
public:
	virtual void Hello()
	{
		std::cout << "hello world" << std::endl;
	}

	void first(mediator_base* _mb)
	{
		mb = _mb;
	}
protected:
	mediator_base* mb;
};

class hand : public base
{
public:
	virtual void Hello()override
	{
		std::cout << "hand ,hello world" << std::endl;
	}

	virtual void eat()
	{
		std::cout << "用手吃饭" << std::endl;
		mb->eat_event();
	}

	virtual void hit_people()
	{
		std::cout << "打人" << std::endl;
		mb->hit_event();		// 中介者u
	}

};

class mouth : public base
{
public:
	virtual void open_mouth()
	{
		std::cout << "open mouth 去吃饭" << std::endl;
	}
};

class mind : public base
{
public:
	virtual void angle()
	{
		std::cout << "我非常生气" << std::endl;
	}
};


class concrete_mediator : public mediator_base
{
public:
	virtual void eat_event()
	{
		_mouth->open_mouth();
	}

	virtual void hit_event()
	{
		_mind->angle();
	}

	template <typename T>
	void set(T * a)
	{
		if constexpr (std::is_same_v<mind, T>)
			_mind = a;
		else if constexpr (std::is_same_v<hand, T>)
			_hand = a;
		else
		{
			_mouth = a;	
		}
	}

private:
	mind* _mind;
	hand* _hand;
	mouth* _mouth;
};

void test_mediator()
{
	concrete_mediator cm;
	mind md;
	hand hd;
	mouth mh;
	md.first(&cm);
	hd.first(&cm);
	mh.first(&cm);
	cm.set<mind>(&md);
	cm.set<hand>(&hd);
	cm.set<mouth>(&mh);


	// hand 发起事件
	hd.Hello();
	hd.eat();
	hd.hit_people();

}