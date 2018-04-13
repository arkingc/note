* **一.变量**
    * 1）全局变量与static变量？（作用域、生存周期）
    * 2）两个.h文件中声明两个同名变量？（使用了与未使用extern） 
    * 3）全局数组和局部数组的初始化？
    * 4）指针和引用的区别？（代表意义、内存占用、初始化、指向是否可改、作为参数、作为返回）
    * 5）C++的四种强制转换
    * 6）[如何修改const变量、const与volatile](https://blog.csdn.net/heyabo/article/details/8745942)
    * 7）静态类型获取与动态类型获取（[typeid](当typeid作用于指针时（而非指针所指的对象），返回的结果是该指针的静态编译时类型)、dynamic_cast:转换目标类型必须是引用类型）
* **二.函数**
    * 1）重载（[参数必须不同(const修饰形参)](https://github.com/arkingc/llc/blob/master/cpp/overload/main.cpp#L9)、重载与作用域、继承中的重载\(using\)、重载与const成员函数） 
* **三.类**
    * 1）面向对象的三大特性（封装、继承、多态）
    * 2）struct和class的区别？
    * 3）[访问权限说明符](../C++/访问控制说明符.md)？（目的是加强类的封装性）
    * 4）类的静态成员（所属、定义时不能重复使用static、静态成员函数与const、类类型的成员、具有类内初始值的静态成员定义时不可再设初值）
    * 5）构造函数相关
        - 有哪些构造函数（默认、委托、拷贝、移动）
        - 合成的默认拷贝构造函数（默认行为？什么情况下不会合成？怎么解决？如果成员包含类内初始值，合成默认构造函数会使用该成员的类内初始值初始化该成员）
        - 拷贝构造函数（调用时机、合成版的行为、explict？、为何第一个参数必须是引用类型）
        - 移动拷贝构造函数（非拷贝而是窃取资源、与noexcept?、何时合成）
        - 可否通过对象或对象的引用(指针或引用)调用
    * 6）初始值列表（顺序、效率(内置类型不进行隐式初始化故无所谓,但..)、无默认构造函数的成员,const成员,引用成员必须通过初始值列表初始化）
    * 7）赋值运算符相关
        - 拷贝赋值运算符（合成版的行为？、与delete？、自定义时要注意自赋值，参数与返回类型、大部分组合了拷贝构造函数与析构函数的工作）
        - 阻止拷贝（某些对象应该独一无二(比方说人)、C++11前:private并且不定义(试图拷贝会报链接错误)，C++11:=delete 《Effective C++:条款6》）
        - 移动赋值运算符（与noexcept？何时合成）
        - 可以定义为成员或非成员函数，定义成成员函数时第一个操作数隐式绑定到this指针
        - 不可重载的操作符有哪些？（?:，::）
    * 8）析构函数相关
        - 销毁过程的理解（delete会执行那些操作？[逆序析构成员](https://github.com/arkingc/llc/blob/master/cpp/class/constructorANDdestructor/order.cpp#L1)）
        - 为什么析构函数中不能抛出异常？（不能是指“不应该”，C++本身并不禁止《Effective C++:条款8》）
        - 如果析构函数中包含可能抛出异常的代码怎么办？（Effective C++:条款8》）
        - 可否通过对象或对象的引用(指针或引用)调用
        - 为什么将继承体系中基类的析构函数声明为虚函数？（delete 指向子类对象的基类指针）
        - 不应该将非继承体系中的类的虚函数声明为虚函数（《Effective C++:条款7》）
        - 不应该继承析构函数非虚的类（《Effective C++:条款7》，可以谈final了）
        - [防止继承的方式](https://blog.twofei.com/672/)
    * 9）[删除的合成函数](https://github.com/arkingc/llc/blob/master/cpp/class/delete/README.md)（一般函数而言不想调用的话不定义就好）
    * 10）继承相关
        - 继承体系中的构造、拷贝、析构顺序？（派生类只负责自己成员的拷贝控制，可以(换而言之非必须，如果不显示调用，会调用父类合成的默认版本)在初始值列表或函数体中调用基类相应函数）
        - 继承中的名字查找（作用域嵌套、从子类到父类查找）
        - 同名名字隐藏（如何解决？(域作用符，从指示的类开始查找)、不同作用域无法重载、using的作用？除此之外呢？） 
        - 虚继承（解决什么问题？(多继承中的子对象冗余)）
    * 11）多态的实现？
    * 12）[虚函数的实现原理？对类大小的影响？](https://www.cnblogs.com/malecrab/p/5572730.html)（vtbl是一个由函数指针组成的数组，无论pb指向哪种类型的对象，只要能够确定被调函数在虚函数中的偏移值，待运行时，能够确定具体类型，并能找到相应vptr，进一步能找出真正应该调用的函数）
    * 13）为什么不要在构造、析构函数中调用虚函数？（子对象的base class构造期间，对象的类型是base class Effective C++:条款9》）
    * 14）[虚函数被隐藏？](https://github.com/arkingc/llc/blob/master/cpp/class/inheritance/virtual_function_hide.cpp#L1)
    * 15）virtual函数动态绑定，缺省参数值静态绑定（《Effective C++:条款37》）
    * 16）纯虚函数与抽象基类（关系、”=0“、必须在类内申明）
    * 17）静态类型与动态类型（引用是否可实现动态绑定）
    * 18）浅拷贝与深拷贝（安全性、行为像值的类与行为像指针的类）
    * 19）如何定义类内常量？（enum而不是static const 《Effective C++:条款3》）
* **四.容器**
    * 1）vector底层的实现？insert具体做了哪些事？resize()调用的是什么（根据新指定大小和当前大小比较，然后插入或删除元素）？
    * 2）map、set的实现原理（红黑树、对于set来说key和value合一，value就是key，map的元素是一个pair，包括key和value、set不支持[]，map(不包括multimap)支持[]）
    * 3）set(map)和multiset(multimap)的区别？（set不允许key重复,其insert操作调用rb_tree的insert_unique函数，multiset允许key重复,其insert操作调用rb_tree的insert_equal函数）
    * 4）set(multiset)和map(multimap)的迭代器（由于set(multiset)key和value合一，迭代器不允许修改key、map(multimap)除了key有data，迭代器允许修改data不允许修改key）
    * 5）map与unordered_map的区别？
* **五.内存管理**
    * 1）[C++内存分区](../C++/内存分区.md)
    * 2）内存管理有几种方式？（new、delete、malloc、free、allocators）
    * 3）new和malloc的区别？（函数，运算符、类型安全、计算空间、步骤）
    * 4）malloc的实现？
    * 5）delete（步骤、delete与析构、可以delete空指针、可以delete动态const对象）
    * 6）为什么要内存对齐？(性能原因、平台原因)
    * 7）[结构体内存对齐方式？](https://github.com/arkingc/llc/blob/master/cpp/alignment/struct.cpp#L1)
    * 8）什么是内存泄露？如何检测与避免？（Mtrace，[valgrind](https://www.ibm.com/developerworks/cn/linux/l-cn-valgrind/)）
    * 9）智能指针相关
        * 种类、区别、原理、能否管理动态数组
        * shared_ptr（使用、计数的变化，get()函数要注意什么）
        * unique_ptr(如何转移控制权)
        * [weak_ptr(特点、用途)](https://www.cnblogs.com/DswCnblog/p/5628314.html)
        * 手写实现智能指针
* **六.关键字**
    * 1）extern？（extern "C"?、与static？、有什么问题？、extern的时候定义变量？）
    * 2）const？（修饰变量、修饰指针与引用、修饰成员函数 《Effective C++:条款3》）
    * 3）mutable？（可变数据成员，[除此之外？](https://github.com/arkingc/llc/blob/master/cpp/class/modify_const_object.cpp)）
    * 4）static？（修饰变量、类中使用）
    * 5）define与const、enum、template inline？（《Effective C++:条款2》、C中默认const是外部连接的，而C++中默认const是内部连接的）
    * 6）explict?（抑制隐式转换、可通过显示转换或直接初始化解决、类外定义时不应重复出现）
    * 7）noexcept？（承诺不会抛出异常）
    * 8）default、delete?（显示要求编译器合成、不能被调用）
    * 9）using？（用于命名空间？、用于类中？）
    * 10）final？（修饰类？、修饰成员函数？）
    * 11）auto？(类型推导、初始化、不能用于函数及模板)
    * 12）volatile?（对象的值可能在程序的控制外被改变时，应将变量申明为volatile，告诉编译器不应对这样的对象进行优化，如果优化，从内存读取后CPU会优先访问数据在寄存器中的结果，但是内存中的数据可能在程序之外被改变、可以既是const又是volatile，const只是告诉程序不能试图去修改它.volatile是告诉编译器不要优化，因为变量可能在程序外部被改变）
* **七.其它**
    * 1）调试程序的方法?
    * 2）遇到coredump要怎么调试？
    * 3）模板的用法与适用场景
    * 4）用过C++11？新特性？（auto,decltype、explicit、lambda、final）
    * 5）C++函数调用的压栈过程
    * 6）sizeof和strlen的区别？（运算符与函数、计算的对象、编译时运行时）
    * 7）union？
    * 8）覆盖、重载与隐藏（覆盖要求参数完全相同，用于继承体系的虚函数中，重载要求参数不同）
    * 9）C++是不是类型安全的？（不是，两个不同类型指针可以强制转换）
    * 10）gcc和g++的区别？（gcc代表GUN Compiler Collection，是一堆编译器的集合，包括g++）
    * 11）[C字符串处理函数](../C++/C字符串处理函数.md)
    * 12）[C内存操作函数](../C++/C内存操作函数.md)
    * 13）[运行时类型识别实现对象比较函数](https://github.com/arkingc/llc/blob/master/cpp/RTTI/RTTI.cpp#L9)
