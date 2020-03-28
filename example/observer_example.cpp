#include "../include/observer.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
USING_DESIGN_PATTERN;

// 猫和老鼠

class cat;
class mouse;

template<typename>
class cm_minix
{
public:
	virtual const char* name()const = 0;
};

using base_cat = observer_patterm_subject_impl<mouse,default_observer_subject_hack_method, cm_minix>;

class cat : public base_cat
{
public:
	cat(const char* cat_name)
		: _cat_name(cat_name)
	{

	}

	virtual const char* name() const override
	{
		return _cat_name;
	}

	virtual void add_observer(mouse* observer)
	{
		if (_mouses.size() == 0 || !std::binary_search(std::begin(_mouses), std::end(_mouses), observer))
		{
			_mouses.push_back(observer);
		}
	}
	virtual void remove_observer(mouse* observer)
	{
		if (_mouses.size() == 0 || !std::binary_search(std::begin(_mouses), std::end(_mouses), observer))
			return;
		_mouses.erase(std::find(std::begin(_mouses), std::end(_mouses), observer));
	}
	virtual void notify()const
	{
		std::for_each(std::begin(_mouses), std::end(_mouses),
			[outer_this = this](auto * v) {v->update(outer_this); });
	}

private:
	std::vector<mouse*> _mouses;
	const char* _cat_name;
};

using mouse_base = observer_pattern_observer_impl<base_cat,default_observer_observer_hack_method,cm_minix>;

class mouse : public mouse_base
{
public:
	mouse(char const * ne)
		:_name(ne){}
	virtual void update(const base_cat* cat) override
	{
		std::cout << cat->name() << "快跑吧! " << name() << "大叫道!!" << std::endl;
	}

	virtual const char* name()const override
	{
		return _name;
	}

private:
	char const* _name;
};

void test_observer()
{
	cat c1("tong cat");
	cat c2("kiki cat");

	mouse m("mi mouse");
	mouse m2("tangly mouse");

	c1.add_observer(&m);
	c1.add_observer(&m2);

	c2.add_observer(&m);
	c2.add_observer(&m2);

	c1.notify();

	c2.notify();
}