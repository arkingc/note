//file：1config10.cpp
//测试template 参数可否根据前一个template参数而设定默认值
//test __STL_LIMITED_DEFAULT_TEMPLATES in <stl_config.h>
//
//编译器：clang-800.0.42.1
 
#include <iostream>  
#include <cstddef>    //for size_t
  
using namespace std;  
  
class alloc  
{  
};  
  
template <class T, class Alloc = alloc, size_t BufSiz = 0>  
class deque  
{  
public:  
  deque()  
  {  
    cout<<"deque"<<endl;  
  }  
};


//根据前一个参数值T，设定下一个参数Sequence的默认值为deque<T>
template <class T, class Sequence = deque<T> >  
class stack  
{  
public:  
  stack()  
  {  
    cout<<"stack"<<endl;  
  }  
private:  
  Sequence c;  
};  
  

int main()  
{ 
  stack<int> x;   //deque
                  //stack
}  