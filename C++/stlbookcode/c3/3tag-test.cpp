#include <iostream>

using namespace std;

struct Input_Iterator_Tag { };
struct Forward_Iterator_Tag : public Input_Iterator_Tag { };
struct Bidirectional_Iterator_Tag : public  Forward_Iterator_Tag { };

template <class I>
void __func(I &p, Input_Iterator_Tag)
{
    cout << " Input_Iterator_Tag version" << endl;
}

template <class I>
void __func(I &p, Bidirectional_Iterator_Tag)
{
    cout << " Bidirectional_Iterator_Tag version" << endl;
}

int main()
{
   int *p;

   __func(p,Input_Iterator_Tag());            // Input_Iterator_Tag version
   //参数与参数未能完全匹配，因继承关系而自动传递调用
   __func(p,Forward_Iterator_Tag());          // Input_Iterator_Tag version
   __func(p,Bidirectional_Iterator_Tag());    // Bidirectional_Iterator_Tag version

    return 0;
}