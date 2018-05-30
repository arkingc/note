* [一.让自己习惯C++](#一让自己习惯c)
    -  [条款02：尽量以const,enum,inline替换\#define](#条款02尽量以constenuminline替换define)
    -  [条款03：尽可能使用const](#条款03尽可能使用const)
* [二.构造/析构/赋值运算](#二构造析构赋值运算)
* [三.资源管理](#三资源管理)
* [四.设计与声明](#四设计与声明)
* [五.实现](#五实现)
* [六.继承与面向对象设计](#六继承与面向对象设计)
* [七.模板与泛型编程](#七模板与泛型编程)
* [八.定制new和delete](#八定制new和delete)
* [九.杂项讨论](#九杂项讨论)    

<br>
<br>
<br>

# 一.让自己习惯C++

## 条款02：尽量以const,enum,inline替换\#define

**这个条款或许改为“宁可以编译器替换预处理器”比较好**

### 1）以const替换\#define

```c++
#define ASPECT_RATIO 1.653
替换为：
const double AspectRatio = 1.653
```

* **处于调试的需要**：#define的记号会被预处理器移走，记号名称可能没进入记号表内。因此当#define的宏名称获得一个编译错误时，会引起困惑，浪费大量时间追踪错误。而AspectRatio肯定会被编译器看到
* **更小的代码量**：对浮点数而言，使用常量可能比使用#define导致较小量的代码，因为预处理器“盲目地将ASPECT_RATIO替换为1.653”可能导致目标码出现多份1.653

但是，以常量替换#define时要注意：

* **定义常量指针时：由于常量定义式通常被定义在头文件内，因此有必要将指针声明为const**。如：
    ```c++
    const char* const authorName = "Scott Meyers";
    ```
* **class专属常量**：class专属常量需要声明在class内部，并且被class使用：
    ```c++
    class GamePlayer{
        static const int NumTurns = 5; //常量声明式
        int scores[NumTurns];          //使用该常量
    };
    //通常定义出现在头文件中
    const int GamePlayer::NumTurns;    //NumTurns的定义
    ```
    对于static修饰的class专属整形常量，如果需要对该常量取地址或编译器坚持要看到一个定义式。那么必须提供类外定义。如果类内声明时提供了初始值，类外定义就不能再设初值。但是某些编译器可能不支持类内初始值，因此需要在类外定义时提供初始值，但是这样就没有像scores成员一样，在类内使用该常量。因此，如果需要使用class专属常量，最好改用“**enum hack**”

### 2）以enum替换\#define

正如说明说提到的，编译器可能不支持类内初始值，因此改用"**enum hack**"：

```c++
class GamePlayer{
    enum {NumTurns = 5};
    int scores[NumTurns];   //这就没问题了
};
```

**enum hack**的行为比较像#define而不像const。例如取一个const的地址时合法的，但取一个enum的地址就不合法，而取一个#define的地址通常也不合法

### 3）以inline替换\#define

以#define实现宏看起来像函数，并且不会导致函数调用带来的开销，但是可能引发错误：

```c++
#define CALL_WITH_MAX(a,b) f((a) > (b) ?  (a) : (b))

int a = 5,b = 0;
CALL_WITH_MAX(++a,b);       //a被累加2次
CALL_WITH_MAX(++a,b + 10);  //a被累加1次
```

使用inline函数可以减轻为参数加上括号以及参数被核算多次等问题。同时，inline可以实现一个“类内的private inline函数”，但一般而言宏无法完成此事

## 条款03：尽可能使用const

### 1）const修饰变量

如果变量本身不应该被修改，应该使用const修饰。这样编译器可以进行保护，确保这个变量不会被修改

```c++
char greeting[] = "Hello";
char *p = greeting;                    // non-const pointer, non-const data
const char *p = greeting;              // non-const pointer, const data
char * const p = greeting;             // const pointer, non-const data
const char * const p = greeting;       // const pointer, const data 
```

* 如果关键字const出现在星号左边，表示被指物是常量
* 如果出现在星号右边，表示指针自身是常量

### 2）const修饰函数

* 修饰参数时，和修饰一般变量相同
* 修改返回值，可以降低因客户错误而造成的意外

```c++
Rational a, b, c;
...
if (a * b = c){ //其实是想做一个比较动作，使用const修饰返回值可以避免这种错误
    ...
}
```

如果a和b都是内置类型。这样的代码直截了当就是不合法。而一个“良好的用户自定义类型”的特征是他们避免与内置类型不兼容。因此对operator\*的定义应该如下：

```c++
const Rational operator*(const Rational& lhs, const Rational& rhs);
```

### 3）const修饰成员函数

const修饰成员函数有2个好处：

1. **可读性**：使得接口容易被理解，可以知道哪个函数可以改动对象哪个函数不行
2. **const修饰的成员函数可以作用于const对象**

但是，使用const修饰成员函数时需要注意，C++对常量性的定义是bitwise constness，即函数const成员函数不应该修改对象的任何成员变量。因此，如果成员变量是一个指针，如果不修改指针而修改指针所指之物，也符合bitwise constness，因此如果不是从bitwise constness的角度，这样也是修改了对象：

```c++
class CTextBlock {
public:
  char& operator[](std::size_t position) const   // bitwise constness声明
  { return pText[position]; }                    // 但其实不恰当
private:
   char* pText;
};

const CTextBlock cctb("Hello"); //声明一个常量对象
char *pc = &cctb[0];            //调用const operator[]取得一个指针，
                                //指向cctb的数据
*pc = 'J';                      //cctb现在有了“Jello”这样的内容
```

还有一种logical constness：一个const成员函数可以修改它所处理的对象内的某些bits，但只有在客户端侦测不出的情况下才行：

```c++
class CTextBlock {
public:
  std::size_t length() const;

private:
  char *pText;
  std::size_t textLength;         // 最近一次计算的文本区块长度
  bool lengthIsValid;             // 目前的长度是否有效
};                                     

std::size_t CTextBlock::length() const{
  if (!lengthIsValid) {                 
    textLength = std::strlen(pText);    //错误！在const成员函数内不能复制给
    lengthIsValid = true;               //textLength和lengthIsValid
  }
  return textLength;
}
```

但是，C++对常量性的定义是bitwise constness的，所以这样的操作非法。解决办法是使用mutable:

```c++
class CTextBlock {
public:
  std::size_t length() const;

private:
  char *pText;
  mutable std::size_t textLength;         // 这些成员变量可能总是会被更改
  mutable bool lengthIsValid;             // 即使在const成员函数内
};                                     

std::size_t CTextBlock::length() const{
  if (!lengthIsValid) {                 
    textLength = std::strlen(pText);    //现在可以这样
    lengthIsValid = true;               //也可以这样
  }
  return textLength;
}
```

总的来说，上面提到了2种“修改”const成员函数中修改对象（修改const对象）的方法

最后，const和non-const版本的函数可能含有重复的代码，如果抽离出来单独成为一个成员函数还是有重复。如果希望去重，可以使用“运用const成员函数实现出其non-const孪生兄弟”的技术：

```c++
class CTextBlock {
public:
    const char& operator[](size_t pos) const{
        ...
    }

    char& operator[](size_t pos){
        return const_cast<char&>(
            static_cast<const TextBlock&>(*this)
                [pos]   
        );
    }
};
```

<br>

# 二.构造/析构/赋值运算

<br>

# 三.资源管理

<br>

# 四.设计与声明

<br>

# 五.实现

<br>

# 六.继承与面向对象设计

<br>

# 七.模板与泛型编程

<br>

# 八.定制new和delete

<br>

# 九.杂项讨论
