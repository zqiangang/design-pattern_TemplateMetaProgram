#ifndef _TEMPLATE_METHOD_HPP_
#define _TEMPLATE_METHOD_HPP_
#include "dp_tool_kits.hpp"
DESIGN_PATTERN_START

/*
 *	模板方法模式
 *	模板模板形参 : master_template , 主要的模板,该模板可以调用 template_method_pattern_impl 和 其他混入类的
 *				 : public 和 protected 方法， master_template 应当提供模板方法的主体部分
 *  模板模板方法们 : minix_types ， 主框架方法所需要的一些方法和数据们
 *  友元声明 : 确保 master_template 可以访问其他混入类的 public 和 protected 方法和数据
*/
template<template<typename> class master_template,
	template<typename> class ... minix_types>
class template_method_pattern_impl :
	public sequence_template_inherit<template_method_pattern_impl<master_template,minix_types...>,master_template, minix_types...>
{
	friend class master_template<template_method_pattern_impl<master_template, minix_types...>>;
};


DESIGN_PATTERN_END
#endif // !_TEMPLATE_METHOD_HPP_
