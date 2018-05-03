/*************************************************************
 <stl_config.h>定义__STL_TEMPLATE_NULL如下：
 
 * ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
 * 	define __STL_TEMPLATE_NULL template<>
 * else
 * 	define __STL_TEMPLATE_NULL
 * endif
 
 这个组态常量常常出现在类似这样的场合：

 * // in <type_traits.h>
 * template <class type> struct __type_traits { ...};
 * __STL_TEMPLATE_NULL struct __type_traits<char> { ...};
 *
 * // in <stl_hash_fun.h>
 * template <class key> struct hash { ...};
 * __STL_TEMPLATE_NULL struct hash<char> { ...};
 * __STL_TEMPLATE_NULL struct hash<unsigned char> { ...};

 展开后就变成了：

 * template <class type> struct __type_traits { ...};
 * template<> struct __type_traits<char> { ...};
 *
 * template <class key> struct hash { ...};
 * template<> struct hash<char> { ...};
 * template<> struct hash<unsigned char> { ...};

 这就是所谓的 class template explicit specialization

 *************************************************************/
 

//file：1config-template-exp-special.cpp
//test __STL_TEMPLATE_NULL in <stl_config.h>
//
//编译器：clang-800.0.42.1

#include <iostream>
#include <functional>

using namespace std;

//C++Builder要求必须完全遵照C++标准规格，必须明白写出 template<>
#define __STL_TEMPLATE_NULL /* blank */

//如果不包裹在命名空间中会报错
namespace xmspace{

template <class Key>
struct hash {
	void operator() () {cout << "hash<T>" << endl;}
};

//explicit specialization
template<> struct hash<char> {
	void operator() () {cout << "hash<char>" << endl;}
};

template<> struct hash<unsigned char> {
	void operator() () {cout << "hash<unsigned char>" << endl;}
};

}//end of xmspace

int main()
{
	xmspace::hash<long> t1;
	xmspace::hash<char> t2;
	xmspace::hash<unsigned char> t3;

	t1();	//hash<T>
	t2();	//hash<char>
	t3();	//hash<unsigned char>

	return 0;
}