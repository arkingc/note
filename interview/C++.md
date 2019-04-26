* **一.变量**
    * 1）全局变量与static变量？（作用域、生存周期）
    * 2）[static函数与普通函数的区别？](temp/C++.md#4static函数与普通函数的区别)
    * 3）两个文件中声明两个同名变量？（使用了与未使用extern？） 
    * 4）全局数组和局部数组的初始化？
    * 5）[指针和引用的区别](https://www.nowcoder.com/ta/nine-chapter/review?page=11)？（代表意义、内存占用、初始化、指向是否可改、能否为空）
    * 6）[C/C++中的强制转换](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE27%E5%B0%BD%E9%87%8F%E5%B0%91%E5%81%9A%E8%BD%AC%E5%9E%8B%E5%8A%A8%E4%BD%9C)
    * 7）[如何修改const变量、const与volatile](https://blog.csdn.net/heyabo/article/details/8745942)
    * 8）静态类型获取与动态类型获取（[typeid](https://github.com/arkingc/llc/blob/master/cpp/RTTI/typeid.cpp#L4)、dynamic_cast:转换目标类型必须是引用类型）
    * 9）[如何比较浮点数大小？](https://blog.csdn.net/jk110333/article/details/8902707)（[直接使用==比较出现错误的例子](https://stackoverflow.com/questions/26261466/in-current-c-and-java-double-type-and-float-type-if-x-0-0-is-correct)）
* **二.函数**
    * 1）重载（[参数必须不同(const修饰形参)](https://github.com/arkingc/llc/blob/master/cpp/overload/main.cpp#L9)、重载与作用域、继承中的重载\(using\)、重载与const成员函数） 
* **三.类**
    * 1）面向对象的三大特性（封装、继承、多态）
    * 2）[struct和class的区别？](https://blog.csdn.net/qq_37964547/article/details/81835488)
    * 3）[访问权限说明符](temp/C++.md/#3访问控制说明符)？（目的是加强类的封装性）
    * 4）类的静态成员（所属？静态成员函数不能声明成const、类类型的成员、定义时不能重复使用static、具有类内初始值的静态成员定义时不可再设初值）
    * 5）构造函数相关
        - 有哪些构造函数（默认、委托、拷贝、移动）
        - 合成的默认拷贝构造函数（默认行为？什么情况下不会合成？怎么解决？如果成员包含类内初始值，合成默认构造函数会使用该成员的类内初始值初始化该成员）
        - 拷贝构造函数（调用时机、合成版的行为、explict？、为何第一个参数必须是引用类型）
        - 移动拷贝构造函数（非拷贝而是窃取资源、与noexcept?、何时合成）
        - 可否通过对象或对象的引用(指针或引用)调用
    * 6）初始值列表（顺序、效率(内置类型不进行隐式初始化故无所谓,但..)、无默认构造函数的成员,const成员,引用成员必须通过初始值列表初始化）
    * 7）赋值运算符相关
        - 拷贝赋值运算符（合成版的行为？、与delete？、自定义时要注意自赋值，参数与返回类型、大部分组合了拷贝构造函数与析构函数的工作）
        - 阻止拷贝（某些对象应该独一无二(比方说人)、C++11前:private并且不定义(试图拷贝会报链接错误)，C++11:=delete [《Effective C++:条款6》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE06%E8%8B%A5%E4%B8%8D%E6%83%B3%E4%BD%BF%E7%94%A8%E7%BC%96%E8%AF%91%E5%99%A8%E8%87%AA%E5%8A%A8%E7%94%9F%E6%88%90%E7%9A%84%E5%87%BD%E6%95%B0%E5%B0%B1%E8%AF%A5%E6%98%8E%E7%A1%AE%E6%8B%92%E7%BB%9D)）
        - 移动赋值运算符（与noexcept？何时合成）
        - 可以定义为成员或非成员函数，定义成成员函数时第一个操作数隐式绑定到this指针
        - 不可重载的操作符有哪些？（?:，::）
    * 8）析构函数相关
        - 销毁过程的理解（delete会执行哪些操作？[逆序析构成员](https://github.com/arkingc/llc/blob/master/cpp/class/constructorANDdestructor/order.cpp#L1)）
        - 为什么析构函数中不能抛出异常？（不能是指“不应该”，C++本身并不禁止[《Effective C++:条款8》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE08%E5%88%AB%E8%AE%A9%E5%BC%82%E5%B8%B8%E9%80%83%E7%A6%BB%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0)）
        - 如果析构函数中包含可能抛出异常的代码怎么办？（Effective C++:条款8》）
        - 可否通过对象或对象的引用(指针或引用)调用
        - 为什么将继承体系中基类的析构函数声明为虚函数？（[《Effective C++:条款7》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE07%E4%B8%BA%E5%A4%9A%E6%80%81%E5%9F%BA%E7%B1%BB%E5%A3%B0%E6%98%8Evirtual%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0)）
        - 不应该将非继承体系中的类的虚函数声明为虚函数（[《Effective C++:条款7》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE07%E4%B8%BA%E5%A4%9A%E6%80%81%E5%9F%BA%E7%B1%BB%E5%A3%B0%E6%98%8Evirtual%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0)）
        - 不应该继承析构函数非虚的类（[《Effective C++:条款7》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE07%E4%B8%BA%E5%A4%9A%E6%80%81%E5%9F%BA%E7%B1%BB%E5%A3%B0%E6%98%8Evirtual%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0)，final防止继承）
        - [防止继承的方式](https://blog.twofei.com/672/)
    * 9）[删除的合成函数](https://github.com/arkingc/llc/blob/master/cpp/class/delete/README.md)（一般函数而言不想调用的话不定义就好）
    * 10）继承相关
        - 继承体系中的构造、拷贝、析构顺序？（派生类只负责自己成员的拷贝控制，可以(换而言之非必须，如果不显示调用，会调用父类合成的默认版本)在初始值列表或函数体中调用基类相应函数）
        - 继承中的名字查找（作用域嵌套、从子类到父类查找；[成员名字的处理](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#%E5%90%8D%E7%A7%B0%E7%9A%84%E7%89%B9%E6%AE%8A%E5%A4%84%E7%90%86)）
        - [成员函数体内、成员函数的参数列表的名字解析时机](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#31-data-member%E7%9A%84%E7%BB%91%E5%AE%9A)（因此，务必将“内嵌的类型声明”放在class起始处）
        - 同名名字隐藏（如何解决？(域作用符，从指示的类开始查找)、不同作用域无法重载、using的作用？除此之外呢？） 
        - 虚继承（解决什么问题？(多继承中的子对象冗余)）
    * 11）多态的实现？
    * 12）[虚函数的实现原理？对类大小的影响？](https://www.cnblogs.com/malecrab/p/5572730.html)（vtbl是一个由函数指针组成的数组，无论pb指向哪种类型的对象，只要能够确定被调函数在虚函数中的偏移值，待运行时，能够确定具体类型，并能找到相应vptr，进一步能找出真正应该调用的函数）
    * 13）为什么不要在构造、析构函数中调用虚函数？（子对象的base class构造期间，对象的类型是base class [《Effective C++:条款9》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE09%E7%BB%9D%E4%B8%8D%E5%9C%A8%E6%9E%84%E9%80%A0%E5%92%8C%E6%9E%90%E6%9E%84%E8%BF%87%E7%A8%8B%E4%B8%AD%E8%B0%83%E7%94%A8virtual%E5%87%BD%E6%95%B0)，[设置虚函数指针的时机](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#vptr%E7%9A%84%E8%AE%BE%E7%BD%AE)）
    * 14）[虚函数被覆盖？](https://github.com/arkingc/llc/blob/master/cpp/class/inheritance/virtual_function_hide.cpp#L1)
    * 15）virtual函数动态绑定，缺省参数值静态绑定（[《Effective C++:条款37》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE37%E7%BB%9D%E4%B8%8D%E9%87%8D%E6%96%B0%E5%AE%9A%E4%B9%89%E7%BB%A7%E6%89%BF%E8%80%8C%E6%9D%A5%E7%9A%84%E7%BC%BA%E7%9C%81%E5%8F%82%E6%95%B0%E5%80%BC)）
    * 16）纯虚函数与抽象基类（[纯虚函数与虚函数、一般成员函数的选择](../C++/EffectiveC++.md#条款34区分接口继承和实现继承)）
    * 17）静态类型与动态类型（引用是否可实现动态绑定）
    * 18）浅拷贝与深拷贝（安全性、行为像值的类与行为像指针的类）
    * 19）如何定义类内常量？（enum而不是static const [《Effective C++:条款2》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE02%E5%B0%BD%E9%87%8F%E4%BB%A5constenuminline%E6%9B%BF%E6%8D%A2define)）
    * 20）继承与组合(复合)之间如何选择？（[《Effective C++:条款38》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE38%E9%80%9A%E8%BF%87%E5%A4%8D%E5%90%88%E5%A1%91%E6%A8%A1%E5%87%BAhas-a%E6%88%96%E6%A0%B9%E6%8D%AE%E6%9F%90%E7%89%A9%E5%AE%9E%E7%8E%B0%E5%87%BA)）
    * 21）private继承？（[《Effective C++:条款39》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE39%E6%98%8E%E6%99%BA%E8%80%8C%E5%AE%A1%E6%85%8E%E5%9C%B0%E4%BD%BF%E7%94%A8private%E7%BB%A7%E6%89%BF)）
    * 22）[如何定义一个只能在堆上（栈上）生成对象的类？](https://www.nowcoder.com/questionTerminal/0a584aa13f804f3ea72b442a065a7618)
    * 23）[内联函数、构造函数、静态成员函数可以是虚函数吗？](https://www.nowcoder.com/ta/nine-chapter/review?page=24)
* **四.内存管理**
    * 1）[C++内存分区](../C++/内存分区.md)
    * 2）[new](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#1new)和malloc的区别？（函数，运算符、类型安全、计算空间、步骤，[operator new的实现](../C++/C++对象模型.md#3operator-new和operator-delete的实现)）
    * 3）[new[]与delete[]？](../C++/C++对象模型.md#4针对数组的new语意)（步骤：如何分配内存，构建对象、如何析构与释放内存？[构造与析构](../C++/C++对象模型.md#3对象数组)）
    * 4）new带括号和不带的区别？（无自定义构造函数时，不带括号的new只分配内存，带括号的new会初始化为0）
    * 5）new时内存不足？（[《Effective C++:条款49》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE49%E4%BA%86%E8%A7%A3new-handler%E7%9A%84%E8%A1%8C%E4%B8%BA)）(new-handler)
    * 6）[malloc](https://github.com/arkingc/note/blob/master/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/UNIX%E7%8E%AF%E5%A2%83%E9%AB%98%E7%BA%A7%E7%BC%96%E7%A8%8B.md#5%E5%AD%98%E5%82%A8%E7%A9%BA%E9%97%B4%E5%88%86%E9%85%8D)、[calloc](https://github.com/arkingc/note/blob/master/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/UNIX%E7%8E%AF%E5%A2%83%E9%AB%98%E7%BA%A7%E7%BC%96%E7%A8%8B.md#5%E5%AD%98%E5%82%A8%E7%A9%BA%E9%97%B4%E5%88%86%E9%85%8D)、[realloc](https://github.com/arkingc/note/blob/master/%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F/UNIX%E7%8E%AF%E5%A2%83%E9%AB%98%E7%BA%A7%E7%BC%96%E7%A8%8B.md#5%E5%AD%98%E5%82%A8%E7%A9%BA%E9%97%B4%E5%88%86%E9%85%8D)、[alloca](https://blog.csdn.net/lan120576664/article/details/38078855)，malloc的实现？
    * 7）调用malloc函数之后，OS会马上分配内存空间吗？（不会，只会返回一个虚拟地址，待用户要使用内存时，OS会发出一个缺页中断，此时，内存管理模块才会为程序分配真正内存）
    * 8）[delete](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#1new)（步骤、delete与析构、可以delete空指针、可以delete动态const对象）
    * 9）为什么要内存对齐？([性能原因、平台原因](temp/C++.md/#1为什么要内存对齐))
    * 10）[struct内存对齐方式？](https://github.com/arkingc/llc/blob/master/cpp/alignment/struct.cpp#L1)
    * 11）如何取消内存对其？（添加预处理指令`#pragma pack(1)`）
    * 12）什么是内存泄露？如何检测与避免？（Mtrace，[valgrind](temp/C++.md/#2valgrind)）
    * 13）[智能指针相关](https://mubu.com/doc/BGwWx-huk)
        * 种类、区别、原理、能否管理动态数组
        * shared_ptr（使用、计数的变化，get()函数要注意什么）
        * unique_ptr(如何转移控制权)
        * [weak_ptr(特点、用途：可以解决shared_ptr的循环引用问题)](https://www.cnblogs.com/DswCnblog/p/5628314.html)
        * 手写实现智能指针
    * 14）[实现memcpy](../数据结构与算法/算法题总结.md#1实现memcpy)
    * 15）memcpy与memmove的区别（前者不处理重叠，后者处理重叠）
    * 16）[能否使用memcpy比较两个结构体对象？](https://blog.csdn.net/peng314899581/article/details/60766892)
    * 17）实现[strlen](../数据结构与算法/算法题总结.md#1实现strlen)、[strcmp](../数据结构与算法/算法题总结.md#2实现strcmp)、[strcat](../数据结构与算法/算法题总结.md#3实现strcat)、[strcpy](../数据结构与算法/算法题总结.md#4实现strcpy)
* **五.STL**
    * 1）[顺序容器与关联容器的比较？](https://blog.csdn.net/JIEJINQUANIL/article/details/51175858)[有哪些顺序容器与关联容器？](https://github.com/arkingc/note/blob/master/pic/stl-4-1.jpeg)
    * 2）[vector底层的实现](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#1vector)（迭代器类型为随机迭代器）？insert具体做了哪些事？[resize()](https://github.com/arkingc/note/blob/master/C%2B%2B/tass-sgi-stl-2.91.57-source/stl_vector.h#L209)调用的是什么？
    * 3）vector的push_back要注意什么（大量调用会伴随大量的拷贝构造与析构，内存分配与释放）
    * 4）vector的resize()与[reserve()](https://github.com/arkingc/note/blob/master/C%2B%2B/tass-sgi-stl-2.91.57-source/stl_vector.h#L129)（[测试程序](https://github.com/arkingc/llc/blob/master/cpp/container/vector/size.cpp#L5)）
    * 5）[如何释放vector的空间？](https://blog.csdn.net/u014774781/article/details/48197891)（swap）、[容器的元素类型为指针？](https://blog.csdn.net/u014774781/article/details/48197891)（会有内存泄露，[指针是trivial_destructor](https://github.com/arkingc/note/blob/master/C%2B%2B/tass-sgi-stl-2.91.57-source/stl_construct.h#L72)；也可以使用智能指针来管理）
    * 6）[vector的clear](https://github.com/arkingc/note/blob/master/C%2B%2B/tass-sgi-stl-2.91.57-source/stl_vector.h#L210)与[deque的clear](https://github.com/arkingc/note/blob/master/C%2B%2B/tass-sgi-stl-2.91.57-source/stl_deque.h#L774)（vector的erase和clear只会析构不会释放内存，deque的erase和clear不但会析构，还可能会释放缓冲区）
    * 7）[list的底层实现](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#23-list%E7%9A%84%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84)（迭代器类型为双向迭代器）
    * 8）[deque的底层实现](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#33-deque%E7%9A%84%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84)（迭代器类型为随机迭代器）
    * 9）vector与deque的区别？（deque能以常数时间在首尾插入元素；deque没有capacity的概念）
    * 10）[map](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#3map)、[set](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#2set)的实现原理（红黑树、对于set来说key和value合一，value就是key，map的元素是一个pair，包括key和value、set不支持[]，map(不包括multimap)支持[]）
    * 11）set(map)和multiset(multimap)的区别？（set不允许key重复,其insert操作调用rb_tree的insert_unique函数，multiset允许key重复,其insert操作调用rb_tree的insert_equal函数）
    * 12）set(multiset)和map(multimap)的迭代器（由于set(multiset)key和value合一，迭代器不允许修改key、map(multimap)除了key有data，迭代器允许修改data不允许修改key）
    * 13）map与[unordered_map](https://blog.csdn.net/hk2291976/article/details/51037095)的区别？（hash_map需要hash函数及等于函数，map只需小于函数）
    * 14）set(multiset)和map(multimap)的迭代器[++操作、--操作的时间复杂度](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#12-rb-tree%E7%9A%84%E8%BF%AD%E4%BB%A3%E5%99%A8)？
    * 15）空间分配器allocator
        - [将new和delete的2阶段操作分离](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#%E4%BA%8C%E7%A9%BA%E9%97%B4%E5%88%86%E9%85%8D%E5%99%A8)（construct和destroy负责内存分配？allocate和deallocate负责对象构造析构？）
        - [SGI符合部分标准的空间分配器——std::allocator](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#%E4%BA%8C%E7%A9%BA%E9%97%B4%E5%88%86%E9%85%8D%E5%99%A8)
        - [SGI特殊的空间分配器——std::alloc](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#3sgi%E7%89%B9%E6%AE%8A%E7%9A%84%E7%A9%BA%E9%97%B4%E5%88%86%E9%85%8D%E5%99%A8stdalloc)（[对象构造与析构](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#31-%E5%AF%B9%E8%B1%A1%E6%9E%84%E9%80%A0%E4%B8%8E%E6%9E%90%E6%9E%84)、内存分配与释放——[两级分配器](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#1%E4%B8%A4%E7%BA%A7%E5%88%86%E9%85%8D%E5%99%A8)）
            + [第一级分配器](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#2%E7%AC%AC%E4%B8%80%E7%BA%A7%E5%88%86%E9%85%8D%E5%99%A8__malloc_alloc_template)（如何仿真new-handler机制？不能直接用C++ new-handler，因为没有使用::operator new）
            + [第二级分配器](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#3%E7%AC%AC%E4%BA%8C%E7%BA%A7%E5%88%86%E9%85%8D%E5%99%A8__default_alloc_template)（为什么要二级分配器？内存池与16个free-list？空间分配和释放的步骤？）
    * 16）[traits与迭代器相应类型](https://github.com/arkingc/note/blob/master/C++/STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90.md#2traits%E7%BC%96%E7%A8%8B%E6%8A%80%E6%B3%95)
* **六.对象内存模型**
    * **数据成员**
        - [成员变量在类对象中的布局规则](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#32-data-member%E7%9A%84%E5%B8%83%E5%B1%80)
        - [通过指针和通过'.'进行Data Member存取的区别](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#33-data-member%E7%9A%84%E5%AD%98%E5%8F%96)
        - 数据成员的布局——[无继承](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#33-data-member%E7%9A%84%E5%AD%98%E5%8F%96)
        - 数据成员的布局——[不含多态的继承](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#2%E4%B8%8D%E5%90%AB%E5%A4%9A%E6%80%81%E7%9A%84%E7%BB%A7%E6%89%BF)（C++标准并未强制指定派生类和基类成员的排列顺序；理论上编译器可以自由安排。在大部分编译器上，基类成员总是先出现，虚基类除外）
        - 数据成员的布局——[含多态的继承](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#3%E5%90%AB%E5%A4%9A%E6%80%81%E7%9A%84%E7%BB%A7%E6%89%BF)（vptr的位置也没有强制规定，放在不同位置分别有什么好处？）
        - 数据成员的布局——[多重继承](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#4%E5%A4%9A%E9%87%8D%E7%BB%A7%E6%89%BF)（基类子对象的排列顺序也没有硬性规定；指针的调整方式？）
        - 数据成员的布局——[虚继承](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#5%E8%99%9A%E7%BB%A7%E6%89%BF)（虚基类子对象的偏移信息记录在虚函数表之前与使用一个额外指针来记录的对比？）
        - [指向数据成员的指针](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#35-%E6%8C%87%E5%90%91data-members%E7%9A%84%E6%8C%87%E9%92%88)
    * **函数成员**
        - [nonstatic成员函数的转换](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#41-member%E7%9A%84%E5%90%84%E7%A7%8D%E8%B0%83%E7%94%A8%E6%96%B9%E5%BC%8F)（目的是为了提供和一般非成员函数相同的效率）
        - [重载成员函数的名字处理](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0%E9%87%8D%E8%BD%BD%E7%9A%84%E5%A4%84%E7%90%86)
        - [static成员函数的转换](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#2static-member-functions%E9%9D%99%E6%80%81%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0)
        - [编译器如何处理经由指针和经由‘.’进行的调用](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#3virtual-member-functions%E8%99%9A%E5%87%BD%E6%95%B0)
        - [指向函数成员的指针](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#43-%E6%8C%87%E5%90%91member-function%E7%9A%84%E6%8C%87%E9%92%88)
        - 虚函数的调用——[单继承](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#1%E5%8D%95%E7%BB%A7%E6%89%BF%E4%B8%AD%E7%9A%84%E8%99%9A%E5%87%BD%E6%95%B0)
        - 虚函数的调用——[多重继承](https://github.com/arkingc/note/blob/master/C++/C++%E5%AF%B9%E8%B1%A1%E6%A8%A1%E5%9E%8B.md#2%E5%A4%9A%E7%BB%A7%E6%89%BF%E4%B8%AD%E7%9A%84%E8%99%9A%E5%87%BD%E6%95%B0)（子类对象关联有多少个虚函数表？不同虚函数表的名称？执行期什么情况下如何调整this指针？）
* **七.关键字**
    * 1）extern？（extern "C"?、与static？、有什么问题？、extern的时候定义变量？）
    * 2）const？（修饰变量、修饰指针与引用、修饰成员函数 [《Effective C++:条款3》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE03%E5%B0%BD%E5%8F%AF%E8%83%BD%E4%BD%BF%E7%94%A8const)）
    * 3）mutable？
    * 4）[static](https://www.nowcoder.com/ta/nine-chapter/review?page=15)？（修饰变量、类中使用）
    * 5）[define与const](https://www.nowcoder.com/questionTerminal/a60c01a7c4ab473e81218ed0b333b4e6)、enum、inline？（[《Effective C++:条款2》](https://github.com/arkingc/note/blob/master/C++/EffectiveC++.md#%E6%9D%A1%E6%AC%BE02%E5%B0%BD%E9%87%8F%E4%BB%A5constenuminline%E6%9B%BF%E6%8D%A2define)、C中默认const是外部连接的，而C++中默认const是内部连接的）
    * 6）explict?（抑制隐式转换、可通过显示转换或直接初始化解决、类外定义时不应重复出现）
    * 7）noexcept？（承诺不会抛出异常）
    * 8）default、delete?（显示要求编译器合成、不能被调用）
    * 9）using？（用于命名空间？、用于类中？）
    * 10）final？（修饰类？、修饰成员函数？只有虚函数能使用final）
    * 11）auto(初始值为引用时类型为所引对象的类型、必须初始化、不能用于函数及模板)、decltype？
    * 12）volatile?（对象的值可能在程序的控制外被改变时，应将变量申明为volatile，告诉编译器不应对这样的对象进行优化，如果优化，从内存读取后CPU会优先访问数据在寄存器中的结果，但是内存中的数据可能在程序之外被改变、可以既是const又是volatile，const只是告诉程序不能试图去修改它.volatile是告诉编译器不要优化，因为变量可能在程序外部被改变）
* **八.其它**
    * 1）调试程序的方法?（[gdb](https://github.com/arkingc/note/blob/master/Linux/Linux%E5%B8%B8%E7%94%A8%E5%91%BD%E4%BB%A4.md#3%E8%B0%83%E8%AF%95%E5%B7%A5%E5%85%B7gdb)）
    * 2）遇到coredump要怎么调试？
    * 3）模板的用法与适用场景
    * 4）用过C++11？新特性？（auto,decltype、explicit、[lambda](https://mubu.com/doc/1ckW18B1Ak)、final）
    * 5）[函数调用的压栈过程](https://arkingc.github.io/2018/01/12/c-stack_frame/)
    * 6）[sizeof](https://github.com/arkingc/llc/blob/master/cpp/sizeof.cpp#L4)和strlen的区别？（运算符与函数、计算的对象、编译时运行时）
    * 7）union？
    * 8）覆盖、重载与隐藏（覆盖要求参数完全相同，用于继承体系的虚函数中，重载要求参数不同）
    * 9）C++是不是类型安全的？（不是，两个不同类型指针可以强制转换）
    * 10）gcc和g++的区别？（gcc代表GUN Compiler Collection，是一堆编译器的集合，包括g++）
    * 11）[运行时类型识别实现对象比较函数](https://github.com/arkingc/llc/blob/master/cpp/RTTI/RTTI.cpp#L9)
    * 12）[使用C++实现线程安全的单例模式](https://www.cnblogs.com/ccdev/archive/2012/12/19/2825355.html)
    * 13）[什么是异常安全？](../C++/EffectiveC++.md#1异常安全的2个条件)
