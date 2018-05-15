* [一.简介](#一简介)
    * [1.GNU源代码开发精神](#1gnu源代码开放精神)
    * [2.STL版本](#2stl版本)
    * [3.SGI STL头文件分布](#3sgi-stl头文件分布)
    * [4.STL六大部件](#4stl六大部件)
* [二.空间分配器](#二空间分配器)
    * [1.空间分配器的标准接口](#1空间分配器的标准接口)
    * [2.SGI标准的空间分配器std::allocator](#2sgi标准的空间分配器stdallocator)
    * [3.SGI特殊的空间分配器std::alloc](#3sgi特殊的空间分配器stdalloc)
        - [3.1 对象构造与析构](#31-对象构造与析构)
        - [3.2 内存分配与释放](#32-内存分配与释放)

<br>
<br>
<br>

# 一.简介

## 1.GNU源代码开放精神

全世界所有的STL实现版本，都源于Alexander Stepanov和Meng Lee完成的原始版本，这份原始版本有Hewlett-Packard Compant(惠普公司)拥有。每一个头文件都有一份声明，允许任何人任意运用、拷贝、修改、传播、贩卖这些代码，无需付费，唯一的条件是必须将声明置于使用者新开发的文件内

这份开放源代码的精神，一般统称为**open source**

**GNU**(音译为“革奴”)，代码**G**UN is **N**ot **U**nix。当时Unix是计算机界主流操作系统，由AT&T Bell实验室的Ken Thompson和Dennis Ritchie创造。原本只是学术上的一个练习产品，AT&T将它分享给许多研究人员。但是当所有研究与分享使这个产品越来越美好时，AT&T开始思考是否应该追加投资，从中获利。于是开始要求大学校园内的相关研究人员签约，要求他们不得公开或透露UNIX源代码，并赞助Berkeley大学继续强化UNIX，导致后来发展出BSD(Berkeley Software Distribution)版本，以及更后来的FreeBSD、OpenBSD、NetBSD...，**Stallman将AT&T的这种行为视为思想禁锢，以及一种伟大传统的沦丧，于是进行了他的反奴役计划，称之为GNU:GUN is Not Unix**，**GNU计划中，早期最著名的软件包括Emacs和GCC，晚期最著名的是Linux操作系统**

**GNU以所谓的GPL(General Public License，广泛开放授权)来保护(或说控制)其成员**：使用者可以自由阅读与修改GPL软件的源码，但如果使用者要传播借助GPL软件而完成的软件，必须也同意GPL规范。这种精神主要是强迫人们分享并回馈他们对GPL软件的改善。得之于人，舍于人

**Cygnus是一家商业公司**，包装并出售自由软件基金会所构造的软件工具，并贩卖各种服务。他们协助芯片厂商调整GCC，在GPL的精神和规范下将GCC源代码的修正公布于世；他们提供GCC运作信息，提升其运行效率，并因此成为GCC技术领域的最佳咨询对象。Cygnus公司之于GCC，地位就像Red Hat公司之于Linux

## 2.STL版本

* **HP实现版本**(HP STL)
    - **所有STL实现版本的始祖**
    - 运行任何人免费使用、拷贝、修改、传播、贩卖这份软件及其说明文件
    - 唯一需要遵守的是：必须在所有文件中加上HP的版本声明和运用权限声明
    - 这种授权不属于GNU GPL范畴，但属于open source范畴
* **P.J. Plauger实现版本**(PJ STL)
    - 继承自HP版本，所有每一个头文件都有HP的版本说明
    - 此外还加上P.J. Plauger的个人版权声明
    - 不属于GNU GPL范畴，也不属于open source范畴
    - **被Visual C++采用**
    - 符号命名不讲究、可读性较低
* **Rouge Wave实现版本**(RW STL)
    - 继承自HP版本，所以每一个头文件都有HP的版本说明
    - 此外还加上Rouge Wave的公司版权声明
    - 不属于GNU GPL范畴，也不属于open source范畴
    - **被C++Builder采用**（C++Builder对C++语言特性支持不错，连带给予了RW版本正面的影响）
    - 可读性不错
* **STLport实现版本**
    - 以SGI STL为蓝本的高度可移植性实现版本
* **SGI STL实现版本**
    - 继承自HP版本，所以每一个头文件都有HP的版本说明
    - 此外还加上SGI的公司版权声明
    - 不属于GNU GPL范畴，但属于open source范畴
    - **被GCC采用**（GCC对C++语言特性支持很好，连带给予了SGI STL正面影响）
    - 可读性很高
    - 为了具有高度移植性，考虑了不同编译器的不同编译能力

## 3.SGI STL头文件分布

1. **C++标准规范下的C头文件**：cstdio，csyflib，cstring，...
2. **C++标准程序库中不属于STL范畴者**：stream，string，...
3. **STL标准头文件(无扩展名)**：vector，deque，list，map，...
4. **C++标准定案前，HP所规范的STL头文件**：vector.h，deque.h，list.h，...
5. **SGI STL内部文件**(**STL真正实现与此**)：stl_vector.h，stl_deque.h，stl_algo.h，...

不同的编译器**对C++语言的支持程度**不尽相同。作为一个希望具备广泛移植能力的程序库，SGI STL准备了一个**环境组态文件**[<stl_config.h>](tass-sgi-stl-2.91.57-source/stl_config.h)，其中定义了许多常量，标示某些组态的成立与否，所有STL头文件都会直接或间接包含这个组态文件，并以条件式写法，让预处理器根据各个常量决定取舍哪一段程序代码，例如：

<div align="center"> <img src="../pic/stl-1-2.png"/> </div>

**组态测试程序**：

* [编译器对组态的支持](stlbookcode/c1/1config.cpp)
* [组态3：__STL_STATIC_TEMPLATE_MEMBER_BUG](stlbookcode/c1/1config3.cpp)
* [组态5：__STL_CLASS_PARTIAL_SPECIALIZATION](stlbookcode/c1/1config5.cpp)
* [组态6：__STL_FUNCTION_TMPL_PARTIAL_ORDER](stlbookcode/c1/1config6.cpp)
* 组态7：__STL_EXPLICIT_FUNCTION_TMPL_ARGS（整个SGI STL内都没有用到这一常量定义）
* [组态8：__STL_MEMBER_TEMPLATES](stlbookcode/c1/1config8.cpp)
* [组态10：__STL_LIMITED_DEFAULT_TEMPLATES](stlbookcode/c1/1config10.cpp)
* [组态11：__STL_NON_TYPE_TMPL_PARAM_BUG](stlbookcode/c1/1config11.cpp)
* [组态：__STL_EXPLICIT_FUNCTION_TMPL_ARGS](stlbookcode/c1/1config-null-template-arguments.cpp)（**bound friend templates**）
* [组态：__STL_TEMPLATE_NULL](stlbookcode/c1/1config-template-exp-special.cpp)（**class template explicit specialization**）

## 4.STL六大部件

<div align="center"> <img src="../pic/stl-1-1.png"/> </div>

最重要的2个是**容器**与**算法**

* **容器**(container)
* **分配器**(Allocator)
* **算法**(Algorithms)
* **迭代器**(Iterrators)
* **适配器**(Adaptors)
* **仿函数**(Functors)

<br>

# 二.空间分配器

在运用层面，不需要关注空间分配器。但是在容器背后，空间分配器负责容器中元素空间的分配

不称作”内存分配器“，是因为分配的空间不一定是内存，可以是磁盘或其它辅助存储介质。可以实现一个获取磁盘空间的allocator。不过这里介绍的空间分配器获取的空间是内存

## 1.空间分配器的标准接口

通常，C++内存分配和释放的操作如下：

```c++
class Foo {...};
Foo *pf = new Foo;
delete pf;
```

* **new内含2阶段操作**：
    - 调用::operator new分配内存
    - 调用构造函数构造对象
* **delete也含2阶段操作**：
    - 调用析构函数析构对象
    - 调用::operator delete释放内存

STL allocator将new和delete的2阶段操作进行了分离：

* 内存分配：由alloc::allocate()负责
* 内存释放：由alloc::deallocate()负责
* 对象构造：由alloc::construct()负责
* 对象析构：由alloc::destroy负责

根据**STL的规范**，以下是allocator的必要接口：

```c++
allocator::value_type
allocator::pointer
allocator::const_pointer
allocator::reference
allocator::const_reference
allocator::size_type
allocator::difference_type

//一个嵌套的class template，class rebind<U> 拥有唯一成员other,是一个typedef，代表allocator<U> 
allocator::rebind

//构造函数
allocator::allocator()
//拷贝构造函数
allocator::allocator(const allocator&)  
template <class U> allocator::allocator(const allocator<U>&)
//析构函数
allocator::~allocator

//返回某个对象的地址，等同于&x
pointer allocator::address(reference x) const   
const_pointer allocator::address(const_reference x) const

//分配空间，足以容纳n个元素
pointer allocator::allocate(size_type n,const void* = 0)
//归还之前分配的空间
void allocator::deallocate(pointer p,size_type n)
//可分配的最大空间
size_type allocator::max_size() const

//通过x，在p指向的地址构造一个对象。相当于new((void*)p) T(x)
void allocator::construct(pointer p,const T& x)
//析构地址p的对象
void allocator::destroy(pointer p)
```

* **只能有限度搭配PJ STL**，因为PJ STL未完全遵循STL规格，其所供应的许多容器都需要一个非标准的空间分配器接口
* **只能有限度地搭配RW STL**，因为RW STL在很多容器身上运用了缓冲区，情况复杂很多
* **完全无法应用于SGI STL**，因为SGI STL在这个项目上根本就脱离了STL标准规格，使用一个专属的、拥有次层配置能力的、效率优越的特殊分配器。事实上SGI STL仍然提供了一个标准的分配器接口

## 2.SGI标准的空间分配器std::allocator

虽然SGI也定义有一个符合部分标准、名为[allocator](tass-sgi-stl-2.91.57-source/defalloc.h)的分配器，但SGI自己从未用过它，也**不建议我们使用**。**主要原因是效率不佳**，只把C++的::operator new和::operator delete做一层薄薄的包装而已

## 3.SGI特殊的空间分配器std::alloc

STL标准规定分配器定义于```<memory>```中，SGI```<memory>```内含两个文件，负责分离的2阶段操作

<div align="center"> <img src="../pic/stl-2-1.png"/> </div>

> 真正在SGI STL中大显身手的分配器（即SGI特殊的空间分配器std::alloc）或为第一级分配器，或为第二级分配器

### 3.1 对象构造与析构

[<stl_construct.h>](tass-sgi-stl-2.91.57-source/stl_construct.h)

<div align="center"> <img src="../pic/stl-2-2.png"/> </div>

> STL还规定分配器必须拥有名为construct()和destroy()的两个成员函数，然而SGI特殊的空间分配器std::alloc并未遵守这一规则，所以实际上这部分不属于std::alloc，属于STL allocator。换句话说，SGI特殊的空间分配器std::alloc不包含”3.1 对象构造与析构“，只包含”3.2 内存分配与释放“

### 3.2 内存分配与释放

SGI对内存分配与释放的设计哲学如下：

* 向system heap申请空间
* 考虑多线程状态
* 考虑内存不足时的应变措施
* 考虑过多“小型区块”可能造成的内存碎片问题（**SGI设计了双层级分配器**）

**C++的内存分配基本操作是::operator new(),内存释放基本操作是::operator delete()。这两个全局函数相当于C的malloc()和free()函数。SGI正是以malloc和free()完成内存的分配与释放**

#### 1）两级分配器

考虑到小型区块所可能造成的内存碎片问题，SGI设计了双层级分配器：

<div align="center"> <img src="../pic/stl-2-3.png"/> </div>

* 第一级分配器
    - 直接使用malloc()和free()
* 第二级分配器
    - 当分配区块超过128bytes时，视为“足够大”，调用第一级分配器
    - 当分配区块小于128bytes时，视为“过小”，为了降低额外负担，采用复杂的memory pool整理方式，不再求助于第一级分配器

无论alloc被定义为第一级或第二级分配器，SGI还为它再包装一个接口，使分配器的接口能够符合STL规格：

```c++
template<class T, class Alloc>
class simple_alloc {

public:
    static T *allocate(size_t n)
                { return 0 == n? 0 : (T*) Alloc::allocate(n * sizeof (T)); }
    static T *allocate(void)
                { return (T*) Alloc::allocate(sizeof (T)); }
    static void deallocate(T *p, size_t n)
                { if (0 != n) Alloc::deallocate(p, n * sizeof (T)); }
    static void deallocate(T *p)
                { Alloc::deallocate(p, sizeof (T)); }
};
```

内部4个函数都是转调用分配器的成员函数。**这个接口使分配器的分配单位从bytes转为个别元素的大小**

<div align="center"> <img src="../pic/stl-2-4.png"/> </div>

#### 2）第一级分配器__malloc_alloc_template

第一级分配器__malloc_alloc_template定义在头文件[<stl_alloc.h>](tass-sgi-stl-2.91.57-source/stl_alloc.h)中：

```c++
//一般而言是线程安全，并且对于空间的运用比较高效
//无“template型别参数”，至于”非型别参数“inst，则完全没派上用场
template <int inst>
class __malloc_alloc_template {

private:
//oom：out of memory ，用来处理内存不足的情况
static void *oom_malloc(size_t);

static void *oom_realloc(void *, size_t);

#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG
    static void (* __malloc_alloc_oom_handler)();
#endif

public:

static void * allocate(size_t n)
{
    void *result = malloc(n);//第一级分配器直接使用malloc()
    //以下无法满足需求时，改用oom_malloc()
    if (0 == result) result = oom_malloc(n);
    return result;
}

static void deallocate(void *p, size_t /* n */)
{
    free(p);//第一级分配器直接使用free()
}

static void * reallocate(void *p, size_t /* old_sz */, size_t new_sz)
{
    void * result = realloc(p, new_sz);//第一级分配器直接使用realloc()
    //以下无法满足需求时，改用oom_realloc()
    if (0 == result) result = oom_realloc(p, new_sz);
    return result;
}

//以下仿真C++的set_new_handler()。可以通过它指定自己的
//out-of-memory handler
//不能直接运用C++ new-handler机制，因为它并非使用::operator new来分配内存
static void (* set_malloc_handler(void (*f)()))()
{
    void (* old)() = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return(old);
}

};

// malloc_alloc out-of-memory handling

#ifndef __STL_STATIC_TEMPLATE_MEMBER_BUG
//初值为0，有待客户设定
template <int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;
#endif

template <int inst>
void * __malloc_alloc_template<inst>::oom_malloc(size_t n)
{
    void (* my_malloc_handler)();
    void *result;

    for (;;) {//不断尝试释放、分配、再释放、再分配...
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
        (*my_malloc_handler)(); //调用处理例程，企图释放内存
        result = malloc(n);     //再次尝试分配内存
        if (result) return(result);
    }
}

template <int inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
    void (* my_malloc_handler)();
    void *result;

    for (;;) {//不断尝试释放、分配、再释放、再分配...
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
        (*my_malloc_handler)(); //调用处理例程，企图释放内存
        result = realloc(p, n); //再次尝试分配内存
        if (result) return(result);
    }
}
```

* 以malloc()、free()、realloc()等C函数执行实际的内存分配、释放、重分配操作
* 实现出类似C++ new-handler的机制（**C++ new-handler机制是，可以要求系统在内存分配需求无法被满足时，调用一个你所指定的函数。换句话说，一旦::operator new无法完成任务，在丢出std::bad_alloc异常状态之前，会先调用由客户指定的处理例程，该处理例程通常即被称为new-handler**），不能直接运用C++ new-handler机制，因为它并非使用::operator new来分配内存

#### 3）第二级分配器__default_alloc_template