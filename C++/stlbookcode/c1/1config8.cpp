//file：1config8.cpp
//测试 class template之内可否再有 template（members）
//test __STL_MEMBER_TEMPLATES in <stl_config.h>
//
//编译器：clang-800.0.42.1

#include <iostream>  
using namespace std;  
  
class alloc  
{  
};  
  
template <class T, class Alloc = alloc>  
class vector  
{  
public:  
  typedef T value_type;  
  typedef value_type* iterator;  
  
  template <class I>  
  void insert(iterator position, I first, I last)  
  {  
    cout<<"insert()"<<endl;  
  }  
};  
  
int main()  
{  
  int ia[5] = {0,1,2,3,4};
    
  vector<int> x;  
  vector<int>::iterator ite = NULL;  
  x.insert(ite, ia, ia+4);            //insert()
  return 1;  
}  