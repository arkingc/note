/*************************************************************
 <stl_config.h>定义__STL_NULL_TMPL_ARGS如下：
 
 * ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
 * 	define __STL_NULL_TMPL_ARGS <>
 * else
 * 	define __STL_NULL_TMPL_ARGS
 * endif
 
 这个组态常量常常出现在类似这样的场合（class template的friend函数声明）：

 * // in <stl_stack.h>
 * template <class T,class Sequence = deque<T> >
 * class stack{
 * 	friend bool operator== __STL_NULL_TMPL_ARGS (const stack &,const stack &);
 * 	friend bool operator< __STL_NULL_TMPL_ARGS (const stack &,const stack &);
 * };

 展开后就变成了：

 * template <class T,class Sequence = deque<T> >
 * class stack{
 * 	friend bool operator== <> (const stack &,const stack &);
 * 	friend bool operator< <> (const stack &,const stack &);
 * };

 这种奇特的语法是为了实现所谓的 bound friend templates，也就是说 class template
 的某个具体实现与其 friend function template 的某个具体实现有一对一的关系

 *************************************************************/
 
//file：1config-null-template-arguments.cpp
//test __STL_NULL_TMPL_ARGS in <stl_config.h>
//
//编译器：clang-800.0.42.1

#include <iostream>
#include <cstddef>	//for size_t

using namespace std;

class alloc{
};

template <class T,class Alloc = alloc,size_t BufSiz = 0>
class deque{
public:
	deque() {cout << "deque" << ' ';}
};

template <class T,class Sequence>
class stack;

template <class T,class Sequence>
bool operator== (const stack<T,Sequence> &x , const stack<T,Sequence> &y);

template <class T,class Sequence>
bool operator< (const stack<T,Sequence> &x , const stack<T,Sequence> &y);


template <class T,class Sequence = deque<T> >
class stack{
	//写成这样是可以的
	friend bool operator== <T> (const stack<T> & , const stack<T> &);
	friend bool operator< <T> (const stack<T> & , const stack<T> &);

	//写成这样也是可以的
	friend bool operator== <T> (const stack & , const stack &);
	friend bool operator< <T> (const stack & , const stack &);

	//写成这样也是可以的
	friend bool operator== <> (const stack & , const stack &);
	friend bool operator< <> (const stack & , const stack &);

	//写成这样不可以
	//friend bool operator== (const stack & , const stack &);
	//friend bool operator< (const stack & , const stack &);
public:
	stack() {cout << "stack" << endl;}
private:
	Sequence c;
};

template <class T,class Sequence>
bool operator== (const stack<T,Sequence> &x , const stack<T,Sequence> &y)
{
	return cout << "operator==" << '\t';
}

template <class T,class Sequence>
bool operator< (const stack<T,Sequence> &x , const stack<T,Sequence> &y)
{
	return cout << "operator<" << '\t';
}


int main()
{
	stack<int> x;				//deque stack
	stack<int> y;				//deque stack

	cout << (x == y) << endl;	//operator==	1
	cout << (x < y) << endl;	//operator==	1

	stack<char> y1;				//deque stack
	//cout << (x == y1) << endl;
	//cout << (x < y1) << endl;
}