* [一.让自己习惯C++](#一让自己习惯c)
    - [条款02：尽量以const,enum,inline替换\#define](#条款02尽量以constenuminline替换define)
    - [条款03：尽可能使用const](#条款03尽可能使用const)
* [二.构造/析构/赋值运算](#二构造析构赋值运算)
    - [条款04：确定对象被使用前已先被初始化](#条款04确定对象被使用前已先被初始化)
    - [条款05：了解C++默默编写并调用那些函数](#条款05了解c默默编写并调用那些函数)
    - [条款06：若不想使用编译器自动生成的函数，就该明确拒绝](#条款06若不想使用编译器自动生成的函数就该明确拒绝)
    - [条款07：为多态基类声明virtual析构函数](#条款07为多态基类声明virtual析构函数)
    - [条款08：别让异常逃离析构函数](#条款08别让异常逃离析构函数)
    - [条款09：绝不在构造和析构过程中调用virtual函数](#条款09绝不在构造和析构过程中调用virtual函数)
    - [条款10：令operator=返回一个reference to \*this](#条款10令operator返回一个reference-to-this)
    - [条款11：在operater=中处理“自我赋值”](#条款11在operater中处理自我赋值)
    - [条款12：复制对象时勿忘其每一个成分](#条款12复制对象时勿忘其每一个成分)
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

正如上面所提到的，编译器可能不支持类内初始值，因此改用"**enum hack**"：

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

<br>

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
* **修饰返回值，可以降低因客户错误而造成的意外**

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

## 条款04：确定对象被使用前已先被初始化

**读取未初始化对象的后果**：读取未被初始化的值会导致不明确的行为。在某些平台上，仅仅只是读取为初始化的值就可能让程序终止，更可能的情况是读入一些“半随机”bits，污染了正在进行读取动作的那个对象，最终导致不可预知的程序行为，以及许多令人不愉快的调试过程

按对象的类型划分：

* **对于内置类型的对象**：永远在使用前初始化
* **类类型的对象**：初始化责任落在构造函数身上
    - **效率上的问题**：
        + 类类型成员的初始化动作发生在构造函数本体之前
        + 内置类型成员的初始化不一定发生在赋值动作的的时间点之前
    比起先调用default构造函数然后再调用copy assignment操作符，单只调用一次copy构造函数比较高效。因此，善用初始化列表有助于提升效率。对于内置类型成员，一般为了保持一致也在初始化列表中给出初始值
    - **初始化顺序**：成员的初始化顺序与类内声明顺序相同

 按对象的作用域与生命周期划分

* **static对象**
    - **non-local static对象**：C++对“定义于不同的编译单元内的non-local static对象”的初始化相对次序并无明确定义
        + global对象
        + 定义于namespace作用域内的对象
        + classes内、file作用域内被声明为static的对象
    - **local static对象**：函数内的local static对象会在“该函数被调用期间”“首次遇上该对象的定义式”时被初始化
        + 函数内被声明为static的对象

因此，如果一个non-local static对象的初始化依赖于另外一个non-local static的初始化，那么可能造成错误。解决方法是使用local static对象替换non-local static对象（参考单例模式）

<br>
<br>

# 二.构造/析构/赋值运算

## 条款05：了解C++默默编写并调用那些函数

一般情况下，编译器会为类合成下列函数：

* **default构造函数**
* **copy构造函数**：编译器生成的版本只是单纯地将来源对象的每一个non-static成员变量拷贝到目标对象
* **copy assignment操作符**：编译器生成的版本只是单纯地将来源对象的每一个non-static成员变量拷贝到目标对象
* **析构函数**：编译器生成的版本是**non-virtual**的

以下情况编译器不会合成**copy assignment操作符**：

* **含有引用成员**：原因在于这种情况下，赋值的目的不明确。是修改引用还是修改引用的对象？如果是修改引用，这是被禁止的。因此编译器干脆拒绝这样的赋值行为
* **含有const成员**：const对象不应该修改
* **父类的copy assignment操作符被声明为private**：无法处理基类子对象，因此也就无法合成

<br>

## 条款06：若不想使用编译器自动生成的函数，就该明确拒绝

**为什么要拒绝**？比如，房产应该是独一无二的，这种情况下应该拒绝对象拷贝动作

一般情况下，不声明相应函数即可拒绝。但是编译器会为类合成一些函数，因此需要显示拒绝

还是以拒绝对象拷贝为例子，拒绝方法包括：

1. **将copy构造函数或copy assignment操作符声明为private，并且不定义**这被用于C++ iostream程序库中）
    + 这种情况下member函数和friend函数还是可以调用，如果member函数或friend函数中执行了复制，会引发**链接错误**。可以使用一个基类，在基类中将copy构造函数或copy assignment操作符声明为private，并且继承这个基类。这样可以将**链接错误**移至**编译期**，因为尝试拷贝时，编译器会试着生成一个copy构造函数和一个copy assignment操作符，这些函数的“编译器合成版”会尝试调用其基类的对应兄弟，而那些调用会被编译器拒绝，因为private
2. **使用delete**（这个在书中没有提到）

<br>

## 条款07：为多态基类声明virtual析构函数

* **为基类声明virtual析构函数**：当基类对象经由一个子类指针被删除，而该基类带有一个non-virtual析构函数，结果未定义——实际执行时通常发生的是对象的derived成分没有销毁，即“局部销毁”，造成资源泄露（因为存在这个问题，所以不要继承一个不被用作基类的类）
* **class不用作基类时，不要将析构函数声明为virtual**：virtual会引入虚函数指针，这会增加空间开销，使得类无法被C函数使用，从而不再移植

<br>

## 条款08：别让异常逃离析构函数

**C++并不禁止析构函数吐出异常，但是并不鼓励这样做**

### 1）原因

如果析构函数吐出异常，程序可能过早结束，异常从析构函数中传播出去，可能会导致不明确的行为

### 2）如何解决

1. **在析构函数中catch异常**，然后调用**abort终止**程序。通过abort抢先置“不明确行为”于死地
2. **在析构函数中catch异常**，然后记录该失败，即**吞掉异常**（通常是个坏主意，因为这样压制了“某些动作失败”的重要信息。但是也比负担“草率结束程序”或”不明确行为带来的风险“好）
3. 重新设计接口，让客户能够在析构前主动调用可能引起异常的函数，然后析构函数中使用一个bool变量，根据用户是否主动调用来决定析构函数中是否应该调用可能引起异常的函数，**让客户拥有主动权**（如果客户没有主动调用，那么当发生异常时也不应该抱怨，因为已经给出了客户自己处理异常的机会）

<br>

## 条款09：绝不在构造和析构过程中调用virtual函数

如果希望在继承体系中根据类型在构建对象时表现出不同行为，可以会想到在基类的构造函数中调用一个虚函数：

```c++
class Transaction {                           //所有交易的基类
public:                                           
    Transaction(){           
        ...                           
        logTransaction();                         
    }
    virtual void logTransaction() const = 0;  //做出一份因类型不同而不同的日志记录
};

class BuyTransaction: public Transaction {        //派生类
public:
    virtual void logTransaction() const;          
};

class SellTransaction: public Transaction {      //派生类
public:
    virtual void logTransaction() const;          
};

```

但是最终调用的virtual函数都是基类的版本。同时，因为是纯虚函数，除非定义该函数，否则将报链接错误

**在子类构造期间，virtual函数绝不会下降到派生类阶层。取而代之的是，对象的作为就像隶属基类类型一样。即派生类对象的基类构造期间，对象的类型是基类而不是派生类；除此之外，若使用运行期类型信息**（如dynamic_cast和typeid），也会把对象视为基类类型（这样对待是合理的：因为子类部分尚未初始化，如果调用的是子类的虚函数，通常会访问子类部分的数据，会引发安全问题）

**同样的道理也适用于析构函数。一旦派生类析构函数开始执行，对象内的派生类成员变量便呈现未定义值，所以C++视它们仿佛不再存在。进入基类析构函数后对象就成为一个基类对象**

如果希望实现最初的功能，即根据类型产生不同日志记录，那么可以在派生类的成员初始化列表中，向基类传递一些类型相关的信息，基类构造函数根据这些信息生成不同的日志记录，此时日志记录的生成函数不再是virtual函数

<br>

## 条款10：令operator=返回一个reference to \*this

这是为了实现“连锁赋值”。这个协议除了适用于operator=，还适用于+=、-=、\*=

> 这只是个协议，并无强制性，如果不遵循，代码一样可通过编译

<br>

## 条款11：在operater=中处理“自我赋值”

考虑如下Widget类：

```c++
class Bitmap {...};
class Widget{
    ...
private:
    Bitmap *pb;
};
```

下面的operator=实现是一份不安全的实现，在自赋值时会出现问题：

```c++
Widget& 
Widget::operator=(const Widget& rhs){
    delete pb;                   // stop using current bitmap
    pb = new Bitmap(*rhs.pb);    // start using a copy of rhs's bitmap
    return *this;                // see Item 10
}
```

要处理自赋值，可以有以下几种方式：

1. **在开头添加“证同测试”**
    ```c++
    Widget& Widget::operator=(const Widget& rhs){
        if (this == &rhs) return *this;
        delete pb;                   // stop using current bitmap
        pb = new Bitmap(*rhs.pb);    // start using a copy of rhs's bitmap
        return *this;                // see Item 10
    }
    ```
    这样做虽然能处理自赋值，但不是异常安全的，如果new时发生异常，对象的pb将指向一块被删除的内存
2. **通过确保异常安全来获得自赋值的回报**
    ```c++
    Widget& Widget::operator=(const Widget& rhs){
        Bitmap *pOrig = pb;               // remember original pb
        pb = new Bitmap(*rhs.pb);         // make pb point to a copy of *pb
        delete pOrig;                     // delete the original pb
        return *this;
    }
    ```
    现在，如果new失败，pb会保持原状。同时也能处理自赋值。如果担心效率可以在开头加上“证同测试”。但是if判断也会引入开销，因此需要权衡自赋值发生的频率
3. **使用copy and swap技术**
    ```c++
    //参数为pass by reference
    Widget& Widget::operator=(const Widget &rhs){
        Widget temp(rhs);
        swap(temp);               // swap *this's data with
        return *this;             // the copy's
    }
    //参数为pass by value
    //这种方式的缺点是代码不够清晰，但是将“copying动作“从函数本体内移至”函数参数构造阶段”
    //却可令编译器有时生成更高效的代码
    Widget& Widget::operator=(Widget rhs){
        swap(rhs);                // swap *this's data with
        return *this;             // the copy's
    }
    ```

<br>

## 条款12：复制对象时勿忘其每一个成分

如果声明自己的copying函数，意思就是告诉编译器你并不喜欢缺省实现中的某些行为。编译器仿佛被冒犯似的，会以一种奇怪的方式回敬：如果你自己写出的copying函数代码不完全，它也不会告诉你

* **copy构造函数**
    - **非继承中**：当为类添加一个新成员时，copy构造函数也需要为新成员添加拷贝代码。否则调用新成员的默认构造函数初始化新成员
    - **继承中**：在派生类的copy构造函数中，不要忘记调用基类的copy构造函数拷贝基类部分。而是使用基类的默认构造函数初始化基类部分
* **copy赋值运算符**
    - **非继承中**：当为类添加一个新成员时，copy赋值运算符中也需要为新成员添加赋值代码，否则新成员会保持不变
    - **继承中**：在派生类的copy赋值运算符中，不要忘记调用基类的copy赋值运算符，否则基类部分会保持不变

<br>
<br>

# 三.资源管理

<br>
<br>

# 四.设计与声明

<br>
<br>

# 五.实现

<br>
<br>

# 六.继承与面向对象设计

<br>
<br>

# 七.模板与泛型编程

<br>
<br>

# 八.定制new和delete

<br>
<br>

# 九.杂项讨论
