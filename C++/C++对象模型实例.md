> 记录gdb调试打印一个类对象的内存分布的方法，方便回顾

<div align="center"> <img src="../pic/g++-version.png"/> </div>

代码如下：

```c++
#include <iostream>

using namespace std;

class Base{
public:
    virtual void f() {cout << "Base::f" << endl;}
    virtual void g() {cout << "Base::g" << endl;}
    virtual void h() {cout << "Base::h" << endl;}
};

class Derived : public Base{
public:
    void print() {cout << "Derived::print" << endl;}
};

int main()
{
    cout << sizeof(Derived) << endl;
    Derived d;
    cout << sizeof(d) << endl;

    return 0;
}
```

[gdb的使用]()

对象的内存模型，虚函数表，已经虚函数指针信息：

<div align="center"> <img src="../pic/c++-mode-exp-1.png"/> </div>

<div align="center"> <img src="../pic/c++-mode-exp-1.png"/> </div>