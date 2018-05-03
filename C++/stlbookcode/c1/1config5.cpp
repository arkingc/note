//file：1config5.cpp
//测试class template partial specialization——在class template的一般化设计
//  之外，特别针对某些template参数做特殊设计
//test __STL_CLASS_PARTIAL_SPECIALIZATION，define in <slt_config.h>
//
//编译器：clang-800.0.42.1

#include <iostream>  
using namespace std;  
  
template <class I, class O>  
struct testClass  
{  
  testClass()  
  {  
    cout<<"I, O"<<endl;  
  }  
};  
  
template <class T>  
struct testClass<T*, T*>  
{  
  testClass()  
  {  
    cout<<"T*,T*"<<endl;  
  }  
};  
  
template <class T>  
struct testClass<const T*, T*>  
{  
  testClass()  
  {  
    cout<<"const T*, T*"<<endl;  
  }  
};  
  
int main()  
{  
  testClass<int, char> obj1;        //I, O
  testClass<int*, int*> obj2;       //T*,T*
  testClass<const int*, int*> obj3; //const T*, T*
  return 1;
}