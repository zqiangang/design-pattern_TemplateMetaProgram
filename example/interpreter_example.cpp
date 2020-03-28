#include "../include/interpreter.hpp"
#include <map>
#include <iostream>
USING_DESIGN_PATTERN;

class context
{
public:
	bool look_up(const char* _name);
	void assign(const char* _name, bool value);
private:
	std::map<char const*, bool> _context;
};

bool context::look_up(const char* _name)
{
	if (_context.find(_name) != std::end(_context))
		return _context[_name];
	return false;
}

void context::assign(const char* _name, bool value)
{
	_context[_name] = value;	
}

class boolexpr
{
public:
	virtual bool evaluate(context &) = 0;
};

using interpreter_booleapr = interpreter_patterm_impl<boolexpr>;

class variable_expr : public interpreter_booleapr
{
public:
	variable_expr(const char* _name)
		:name(_name)
	{

	}
	virtual bool evaluate(context &_context)override
	{
		return _context.look_up(name);
	}
private:
	char const* name;
};

class and_expr : public boolexpr
{
public:
	and_expr(boolexpr * _expr1,boolexpr * _expr2)
		:expr1(_expr1),expr2(_expr2)
	{}
	virtual bool evaluate(context & _context)
	{
		return expr1->evaluate(_context) && expr2->evaluate(_context);
	}

private:
	boolexpr* expr1;
	boolexpr* expr2;
};
class or_expr : public boolexpr
{
public:
	or_expr(boolexpr* _expr1, boolexpr* _expr2)
		:expr1(_expr1), expr2(_expr2)
	{}
	virtual bool evaluate(context & _context)
	{
		return expr1->evaluate(_context) || expr2->evaluate(_context);
	}

private:
	boolexpr* expr1;
	boolexpr* expr2;
};

class constant : public boolexpr
{
public:
	constant(bool v)
		:_value(v)
	{}
	virtual bool evaluate(context &)override
	{
		return _value;
	}
private:
	bool _value;
};

class not_expr : public boolexpr
{
public:
	not_expr(boolexpr* _expr1)
		:expr1(_expr1)
	{}
	virtual bool evaluate(context& _context)
	{
		return !expr1->evaluate(_context);
	}

private:
	boolexpr* expr1;
};

void test_interpreter()
{
	boolexpr* expression;
	context ctext;
	ctext.assign("X", false);
	ctext.assign("Z", true);
	ctext.assign("Y", false);
	// = (x and true) or (y and (z or not(false))) = (false && true) || (false && (true || !false)) = false
	expression = new or_expr(
		new and_expr(new variable_expr("X"), new constant(true)),
		new and_expr(new variable_expr("Y"),
			new or_expr(new variable_expr("Z"), new not_expr(new constant(false))))
	);
	std::cout << std::boolalpha;
	std::cout << expression->evaluate(ctext) << std::endl;
	std::cout << "X : " <<ctext.look_up("X") << std::endl;
	std::cout << "Y : " <<ctext.look_up("Y") << std::endl;
	std::cout << "Z : " <<ctext.look_up("Z") << std::endl;
}