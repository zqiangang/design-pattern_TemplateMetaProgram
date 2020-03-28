#include "../include/factory_method.hpp"
USING_DESIGN_PATTERN;

 //step.1
class document
{
public:
	virtual void save() = 0;
	virtual void edit() = 0;
};

 //step.2.0
template <typename T>
class test_hack
{
public:
	using product_point = std::add_pointer_t<T>;
	using product_type = T;
	virtual product_point factory_test_method() = 0;
};
 //step.2.1
template <typename derived_type>
class fe_custom
{
public:
	using CS_T = int;
	virtual void Test_Hack()
	{
		std::cout << "call test hack" << std::endl;
		static_cast<derived_type*>(this)->factory_test_method();
	}

	virtual void call_other()
	{
		std::cout << "other func" << std::endl;
	}
};
 //step.3
using document_productor = design_pattern::factory_method_productor<document>;
using document_creator = design_pattern::factory_method_creator<document_productor>;
using document_creator_custom = design_pattern::factory_method_creator<document_productor,test_hack,fe_custom>;

 //step.4 使用

// product 
class ppt_doc : public document_productor
{
public:
	virtual void save()
	{
		std::cout << "ppt document save" << std::endl;
	}
	virtual void edit()
	{
		std::cout << "ppt document edit" << std::endl;
	}
};

class word_doc : public document_productor
{
public:
	virtual void save()
	{
		std::cout << "word document save" << std::endl;
	}
	virtual void edit()
	{
		std::cout << "word document edit" << std::endl;
	}
};

// createor

class ppt_ct : public document_creator
{
public:
	virtual product_point factory_method()override
	{
		std::cout << "重载 factory method 成功" << std::endl;
		std::cout << "ppt creator" << std::endl;
		return nullptr;
	}
};

class word_ct : public document_creator
{
public:
	virtual product_point factory_method()override
	{
		std::cout << "重载 factory method 成功" << std::endl;
		std::cout << "word creator" << std::endl;
		return nullptr;
	}
};


class word_cs : public document_creator_custom
{
public:
	virtual product_point factory_test_method()override
	{
		std::cout << "test hack cuctom" << std::endl;
		std::cout << "成功自定义 hack" << std::endl;
		return nullptr;
	}
};

class ppt_cs : public document_creator_custom
{
public:
	virtual product_point factory_test_method()override
	{
		std::cout << "word test hack" << std::endl;
		return nullptr;
	}
};

void test_factory_method()
{
	std::cout << "****************************** factory method ******************************" << std::endl;
	std::cout << "-----------------------------------------------" << std::endl;
	// 使用默认的 hack 和 minix
	document_creator* dc = new ppt_ct();
	dc->factory_method();
	dc->default_call_factory_method();

	delete dc;
	// 

	std::cout << "-----------------------------------------------" << std::endl;

	dc = new word_ct();
	dc->factory_method();
	dc->default_call_factory_method();
	
	delete dc;
	std::cout << "-----------------------------------------------" << std::endl;
	document_creator_custom* dcc = new ppt_cs();
	//dcc->
	dcc->factory_test_method();
	dcc->call_other();
	dcc->Test_Hack();

	delete dcc;

	std::cout << "-----------------------------------------------" << std::endl;
	dcc = new word_cs();

	
	dcc->factory_test_method();
	dcc->call_other();
	dcc->Test_Hack();
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "****************************** factory method ******************************" << std::endl;
}


