//file：1config3.cpp
//测试在class template中拥有static data members
//test __STL_STATIC_TEMPLATE_MEMBER_BUG，define in <slt_config.h>
//
//编译器：clang-800.0.42.1


#include <iostream>  
using namespace std;  
  
template <typename T>  
class testclass  
{  
public:  
  static int _data;  
};  

template<> int testclass<int>::_data = 1;  
template<> int testclass<char>::_data = 2;  
  
int main()  
{  
  cout<<testclass<int>::_data<<endl;  //1
  cout<<testclass<char>::_data<<endl; //2
  
  testclass<int> obji1, obji2;  
  testclass<char> objc1, objc2;  
  
  cout<<obji1._data<<endl;            //1
  cout<<obji2._data<<endl;            //1
  cout<<objc1._data<<endl;            //2
  cout<<objc2._data<<endl;            //2
  
  obji1._data = 3;  
  objc2._data = 4;  
    
  cout<<obji1._data<<endl;            //3
  cout<<obji2._data<<endl;            //3
  cout<<objc1._data<<endl;            //4
  cout<<objc2._data<<endl;            //4
  
  return 1;  
}  
