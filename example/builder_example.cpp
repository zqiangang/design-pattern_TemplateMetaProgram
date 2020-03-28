#include "../include/builder.hpp"
#include <iostream>

class core
{
public:
	virtual void content() = 0;
	virtual void add(core*)
	{

	}
};

class word : public core
{
public:
	virtual void content()
	{
		std::cout << "我是字" << std::endl;
	}
};

class text : public core
{
public:
	virtual void content() override
	{
		std::cout << "好多字" << std::endl;
	}

	virtual void add(core* word)
	{
		if (idx == 10) return;
		content_words[idx++] = word;
	}
private:
	std::size_t idx = 0;
	core * content_words[10];
};

class page : public core
{
public:
	virtual void content() override
	{
		std::cout << "好多字text" << std::endl;
	}

	virtual void add(core* text)
	{
		if (idx == 10) return;
		content_words[idx++] = text;
	}
private:
	std::size_t idx = 0;
	core* content_words[10];
};

class book : public core
{
public:
	virtual void content()override
	{
		std::cout << "其中包含了许多字和文字" << std::endl;
	}

	virtual void add(core* page)
	{
		if (idx == 10) return;
		content_words[idx++] = page;
	}
private:
	std::size_t idx = 0;
	core* content_words[10];
};

// 上述工作环境 bool -> n个 -> page -> n个 -> text -> n个 -> word;
// 创建一本书

template <typename T>			// 模板参数 T 为了符合 模板模板参数要求,此处用不到模板参数 T
class _builder_book				// 通过 T 和 默认的 get_build_object() 合作,进行一些所需的数据访问
{
public:
	virtual void build_word() = 0;
	virtual void build_text() = 0;
	virtual void build_page() = 0;
};

using builder_book = design_pattern::builder_pattern_impl<book, design_pattern::default_builder_hack_method, _builder_book>;

class first_builder : public builder_book
{
public:
	virtual void build_word()override
	{
		std::cout << "创建许多字 添加到 book" << std::endl;
		//get_build_object()->add(new word());
	}

	virtual void build_text()override
	{
		std::cout << "创建许多text 添加到 book" << std::endl;
	}

	virtual void build_page()override
	{
		std::cout << "创建许多 page 添加到 book" << std::endl;
	}
};

void test_builder()
{
	std::cout << "****************************** builder ******************************" << std::endl;
	
	builder_book* bbook = new first_builder();
	bbook->first();			// 首先初始化,此处 book 可以默认构造,所以不需要重定义 first 函数
	bbook->build_word();
	bbook->build_text();
	bbook->build_page();
	bbook->result();		// 成功建造一本书,获取这本书,该函数无需重定义
	//bbook->get_build_object();   // 此函数和 result 实现相同,调用需要 this 为 const 是
	//bbook->get_build_object();		// error
	static_cast<builder_book const*>(bbook)->get_build_object();	// ok

	std::cout << "****************************** builder ******************************" << std::endl;
}