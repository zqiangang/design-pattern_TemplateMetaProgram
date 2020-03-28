#include "../include/strategy.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

class context;
using mystrategy = strategy_pattern_impl<context>;

class context
{
public:
	context(mystrategy * strategy = nullptr)
		:mst(strategy)
	{
		mst->first(this);
	}
	void change(mystrategy* strategy)
	{
		if (mst != nullptr)
			delete mst;

		mst = strategy;
		mst->first(this);
	}

	void show() const
	{
		mst->compose();
	}
	const char* d1 = "风娃娃";
	const char* d2 = "风筝";
	const char* d3 = "吹的";
	const char* d4 = "被";
	const char* d5 = "无影无踪";
private:
	mystrategy *mst;
};



class strategy1 : public mystrategy
{
public:
	virtual void compose()override
	{
		std::cout << get_context()->d1 << get_context()->d4 << get_context()->d2 
			<< get_context()->d3 << get_context()->d5 << std::endl;
	}
};

class strategy2 : public mystrategy
{
public:
	virtual void compose()override
	{
		std::cout << get_context()->d2 << get_context()->d4 << get_context()->d1
			<< get_context()->d3 << get_context()->d5 << std::endl;
	}
};

void test_strategy()
{
	context ct(new strategy1);
	ct.show();
	ct.change(new strategy2());
	ct.show();
}