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
		std::cout << "������" << std::endl;
	}
};

class text : public core
{
public:
	virtual void content() override
	{
		std::cout << "�ö���" << std::endl;
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
		std::cout << "�ö���text" << std::endl;
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
		std::cout << "���а���������ֺ�����" << std::endl;
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

// ������������ bool -> n�� -> page -> n�� -> text -> n�� -> word;
// ����һ����

template <typename T>			// ģ����� T Ϊ�˷��� ģ��ģ�����Ҫ��,�˴��ò���ģ����� T
class _builder_book				// ͨ�� T �� Ĭ�ϵ� get_build_object() ����,����һЩ��������ݷ���
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
		std::cout << "��������� ��ӵ� book" << std::endl;
		//get_build_object()->add(new word());
	}

	virtual void build_text()override
	{
		std::cout << "�������text ��ӵ� book" << std::endl;
	}

	virtual void build_page()override
	{
		std::cout << "������� page ��ӵ� book" << std::endl;
	}
};

void test_builder()
{
	std::cout << "****************************** builder ******************************" << std::endl;
	
	builder_book* bbook = new first_builder();
	bbook->first();			// ���ȳ�ʼ��,�˴� book ����Ĭ�Ϲ���,���Բ���Ҫ�ض��� first ����
	bbook->build_word();
	bbook->build_text();
	bbook->build_page();
	bbook->result();		// �ɹ�����һ����,��ȡ�Ȿ��,�ú��������ض���
	//bbook->get_build_object();   // �˺����� result ʵ����ͬ,������Ҫ this Ϊ const ��
	//bbook->get_build_object();		// error
	static_cast<builder_book const*>(bbook)->get_build_object();	// ok

	std::cout << "****************************** builder ******************************" << std::endl;
}