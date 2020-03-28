#include "../include/singleton.hpp"
#include <iostream>
USING_DESIGN_PATTERN;

#ifndef DEFAULT_ENABLE_SECOND_SINGLETON

class test_sing
{
protected:
	test_sing()
	{
		std::cout << "inherit default test_sing" << std::endl;
	}
public:
	void hello()
	{
		std::cout << "inherit hello world" << std::endl;
	}
};
using tsing = design_pattern::singleton_pattern_impl<test_sing>;

#else

class test_sing : public singleton_pattern_impl<test_sing>
{
protected:
	test_sing()
	{
		std::cout << "crtp default test_sing" << std::endl;
	}
public:
	void hello()
	{
		std::cout << "crtp hello world" << std::endl;
	}

	friend class singleton_pattern_impl<test_sing>;					// 注意如果继承类的构造函数不是 public 则必须声明 friend 到 singleton_pattern_impl<> 基类
};

#endif


void test_singleton()
{
#ifndef DEFAULT_ENABLE_SECOND_SINGLETON
	//tsing ts;		// error
	tsing::Instance()->hello();
#else
	test_sing::Instance()->hello();
#endif

}