#include "../include/iterator.hpp"
USING_DESIGN_PATTERN;
#include <iostream>

class mydate
{
public:
	using value_type = int;

	int size() const
	{
		return 20;
	}

	void first()
	{
		for (int i = 0; i < 20; ++i)
			datas[i] = i;
	}

	int* get(int idx)
	{
		return &datas[idx];
	}

private:
	int datas[20];
};

using proxy_iterator_type = iterator_pattern_impl<mydate>;

class proxy_data
{
public:
	using value_type = typename mydate::value_type;
	proxy_data()
		:_md(new mydate())
	{
		_md->first();
	}

	proxy_iterator_type* create_iterator()
	{
		auto *tmp = new proxy_iterator_type();
		tmp->first(_md);
		return tmp;
	}

private:
	mydate* _md;
};



void test_iterator()
{
	proxy_data pd;
	proxy_iterator_type* pi = pd.create_iterator();


	// ±éÀú pd µÄÔªËØ
	for (; !pi->is_done(); pi->next())
		std::cout << *pi->current_element() << std::endl;
}