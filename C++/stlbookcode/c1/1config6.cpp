//file：1config6.cpp
//test __STL_FUNCTION_TMPL_PARTIAL_ORDER in <stl_config.h>
//
//编译器：clang-800.0.42.1

#include <iostream>
using namespace std;

class alloc{
};

template <class T,class Alloc = alloc>
class vector{
public:
	void swap(vector<T,Alloc>&) { cout << "swap()" << endl;}
};

/**********************************
只为说明，非本程序内容

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class T,class Alloc>
inline void swap(vector<T,Alloc> &x,vector<T,Alloc> &y)
{
	x.swap(y);
}
#endif

**********************************/

int main()
{
	vector<int> x,y;
	swap(x,y);			//没有输出swap()
}