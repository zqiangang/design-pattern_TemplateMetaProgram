#include "../include/visitor.hpp"
#include <iostream>
#include <list>
USING_DESIGN_PATTERN;

class vdog;
class vcat;
class zoo;

class _zoo_visitor
{
public:
	virtual void visit(vdog*) = 0;
	virtual void visit(vcat*) = 0;
	virtual void visit(zoo*) = 0;
};

using zoo_visitor = visitor_visitor_pattern_impl<_zoo_visitor>;

template <typename>
class element_minix
{
public:
	virtual const char* name()const = 0;
	virtual int piece()const = 0;
};
// 声明别名
using something = visitor_element_pattern_impl<zoo_visitor, default_visitor_hack_method, element_minix>;

class vdog : public something
{
public:
	vdog(const char* _nm)
		:_name(_nm){}

	virtual const char* name()const override
	{
		return _name;
	}

	virtual int piece()const override
	{
		return 66;
	}

	virtual void accept(visitor_type* vt)override
	{
		vt->visit(this);
	}

private:
	const char* _name;
};

class vcat : public something
{
public:
	vcat(const char* _nm)
		:_name(_nm) {}

	virtual const char* name()const override
	{
		return _name;
	}

	virtual int piece()const override
	{
		return 66;
	}

	virtual void accept(visitor_type* vt)override
	{
		vt->visit(this);
	}

private:
	const char* _name;
};

class zoo : public something
{
public:
	zoo()
		: _name("动物园")
	{}

	void add(something* animal)
	{
		animals.push_back(animal);
	}

	virtual const char* name()const override
	{
		return _name;
	}

	virtual int piece()const override
	{
		return 0;
	}

	virtual void accept(visitor_type* vt)override
	{
		for (decltype(auto) m : animals)
			m->accept(vt);
		vt->visit(this);
	}

private:
	const char* _name;
	std::list<something*> animals;
};

class piece_visitor : public zoo_visitor
{
public:
	virtual void visit(vdog*d)
	{
		total += d->piece();
	}
	virtual void visit(vcat*c)
	{
		total += c->piece();
	}
	virtual void visit(zoo*z)
	{
		total += z->piece();
	}

	int get_piece()
	{
		return total;
	}
private:
	int total = 0;
};


class count_visitor : public zoo_visitor
{
public:
	virtual void visit(vdog* d)
	{
		total += 1;
	}
	virtual void visit(vcat* c)
	{
		total += 1;
	}
	virtual void visit(zoo* z)
	{
		total += 1;
	}

	int get_count()
	{
		return total;
	}
private:
	int total = 0;
};

void test_visitor()
{
	zoo azoo;
	azoo.add(new vcat("cat A"));
	azoo.add(new vcat("cat B"));
	azoo.add(new vcat("cat C"));
	azoo.add(new vcat("cat D"));
	azoo.add(new vcat("cat E"));
	azoo.add(new vdog("dog A"));
	azoo.add(new vdog("dog B"));
	azoo.add(new vdog("dog C"));
	azoo.add(new vdog("dog D"));

	piece_visitor pv;
	count_visitor cv;

	azoo.accept(&pv);
	std::cout << pv.get_piece() << std::endl;

	azoo.accept(&cv);
	std::cout << cv.get_count() << std::endl;
}
