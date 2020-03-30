#include "../include/composite.hpp"
USING_DESIGN_PATTERN;

class Composite;

class Component
{
public:
	virtual Composite* GetComponent() { return nullptr; }
};

class OtherMinixConponent
{
public:
	// ... 
};

using Base_Component = composite_pattern_impl<Component, OtherMinixConponent>;

class Composite : public Base_Component
{
public:
	virtual Composite* GetComponent()override
	{
		return this;
	}
};


class SimpleComponent : public Component
{
public:
	// ... ʹ�� component ��ȱʡ GetComponent
};

class CompositeComponent : public Composite
{
public:
	// ... Ĭ��ʹ�� conposite �� GetComposite
};
