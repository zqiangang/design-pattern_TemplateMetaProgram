#include "../include/template_method.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

template <typename dervied_type>
class master_template
{
protected:
	dervied_type const* dervied()const
	{
		return static_cast<dervied_type const*>(this);
	}

	dervied_type* dervied()
	{
		return static_cast<dervied_type*>(this);
	}

public:
	void accumulate(int* array_data, int length)
	{
		for (int i = 0; i < length; ++i)
		{
			if (dervied()->checker(array_data[i]))
				dervied()->action(array_data[i]);
		}
	}
};

template <typename dervied_type>
class minix_template
{
public:
	virtual void show() const= 0;
protected:
	virtual bool checker(int value) const { return true; }
	virtual void action(int i) = 0;
};

using my_tmethod = template_method_pattern_impl<master_template, minix_template>;

class add_tmethod : public my_tmethod
{
public:
	add_tmethod()
		:_result(0)
	{}

	virtual void show() const
	{
		std::cout << "add result : " << _result << std::endl;
	}
protected:
	virtual bool checker(int value) const override
	{
		return true;
	}
	virtual void action(int i)
	{
		_result += i;
	}
private:
	int _result;
};

class less_0_add_method : public my_tmethod
{
public:
	less_0_add_method()
		:_result(0)
	{}

	virtual void show() const
	{
		std::cout << "less 0 add result : " << _result << std::endl;
	}
protected:
	virtual bool checker(int value) const override
	{ 
		return value < 0;
	}
	virtual void action(int i)
	{
		_result += i;
	}
private:
	int _result;
};

void test_template_method()
{
	my_tmethod* mt = new add_tmethod();
	int arr_date[] = { -10,-20,2,3,4,5,-9,-40,20,40,90,-49 };
	mt->accumulate(arr_date, sizeof(arr_date)/sizeof(int));
	mt->show();

	delete mt;

	mt = new less_0_add_method();
	mt->accumulate(arr_date, sizeof(arr_date) / sizeof(int));
	mt->show();

	delete mt;
}