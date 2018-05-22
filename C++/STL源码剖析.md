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
            + [1）两级分配器](#1两级分配器)
            + [2）第一级分配器__malloc_alloc_template](#2第一级分配器__malloc_alloc_template)
            + [3）第二级分配器__default_alloc_template](#3第二级分配器__default_alloc_template)
        - [3.3 内存基本处理工具](#33-内存基本处理工具)
* [三.迭代器与traits编程技法](#三迭代器与traits编程技法)
    - [1.迭代器相应类型](#1迭代器相应类型)
    - [2.traits编程技法](#2traits编程技法)
    - [3.std::iterator的保证](#3stditerator的保证)
    - [4.SGI STL的__type_traits](#4sgi-stl的__type_traits)
* [四.顺序容器](#四顺序容器)
    - [1.vector](#1vector)
    - [2.list](#2list)
    - [3.deque](#3deque)
    - [4.stack](#4stack)
    - [5.queue](#5queue)
    - [6.heap](#6heap)
    - [7.priority_queue](#7priority_queue)
    - [8.slist](#8slist)
* [五.关联容器](五关联容器)

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
* **完全无法应用于SGI STL**，因为SGI STL在这个项目上根本就脱离了STL标准规格，使用一个专属的、拥有次层配置能力的、效率优越的特殊分配器。但提供了一个对其进行了封装的名为simple_alloc的分配器，符合部分标准

## 2.SGI标准的空间分配器std::allocator

虽然SGI也定义有一个**符合”部分“标准**、名为[allocator](tass-sgi-stl-2.91.57-source/defalloc.h)的分配器，但SGI自己从未用过它，也**不建议我们使用**。**主要原因是效率不佳**，只把C++的::operator new和::operator delete做一层薄薄的包装而已

## 3.SGI特殊的空间分配器std::alloc

STL标准规定分配器定义于```<memory>```中，SGI```<memory>```内含两个文件，负责分离的2阶段操作

<div align="center"> <img src="../pic/stl-2-1.png"/> </div>

> 真正在SGI STL中大显身手的分配器（即SGI特殊的空间分配器std::alloc）或为第一级分配器，或为第二级分配器

### 3.1 对象构造与析构

[<stl_construct.h>](tass-sgi-stl-2.91.57-source/stl_construct.h)

<div align="center"> <img src="../pic/stl-2-2.png"/> </div>

> STL规定分配器必须拥有名为construct()和destroy()的两个成员函数，然而SGI特殊的空间分配器std::alloc并未遵守这一规则，所以实际上这部分属于STL allocator，但不属于std::alloc。换句话说，SGI特殊的空间分配器std::alloc不包含”3.1 对象构造与析构“，只包含”3.2 内存分配与释放“

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

> 上图中Alloc=alloc中的缺省alloc可以是第一级分配器，也可以是第二级分配器。SGI STL已经把它设为第二级分配器

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

第二级分配器多了一些机制，避免太多小额区块造成内存的碎片，小额区块存在下列问题：

* 产生内存碎片
* 额外负担。额外负担是一些区块信息，用以管理内存。区块越小，额外负担所占的比例就越大，越显浪费

<div align="center"> <img src="../pic/stl-2-5.png"/> </div>

* 当区块大于128bytes时，视为大区块
    - 转交第一级分配器处理
* 当区块小于128bytes时，视为小额区块
    - 以**内存池管理(也称为次层分配)**：每次分配一大块内存，并维护对应的自由链表(free-list)，下次若载有相同大小的内存需求，就直接从free-list中拨出。如果客户释放小额区块，就由分配器回收到free-list中。**维护有16个free-list**，各自管理大小分别为8，16，24，32，40，48，56，64，72，80，88，96，104，112，120，128bytes的小额区块
    - SGI第二级分配器会主动将任何小额区块的内存需求量上调至8的倍数

free-list使用如下结构表示：

```c++
//使用union解决free-list带来的额外负担：维护链表所必须的指针而造成内存的另一种浪费
union obj{
    union obj * free_list_link; //系统视角
    char client_data[1];        //用户视角
}
```

下图是free-list的实现技巧：

<div align="center"> <img src="../pic/stl-2-6.png"/> </div>

第二级分配器__default_alloc_template也定义在头文件[<stl_alloc.h>](tass-sgi-stl-2.91.57-source/stl_alloc.h)中，以下为部分实现：

```c++
#ifdef __SUNPRO_CC
// breaks if we make these template class members:
  enum {__ALIGN = 8};                           //小型区块的上调边界
  enum {__MAX_BYTES = 128};                     //小型区块的上限
  enum {__NFREELISTS = __MAX_BYTES/__ALIGN};    //free-list的个数
#endif

//第二级分配器的定义
//无”template型别参数“，第一个参数用于多线程环境，第二参数完全没派上用场
template <bool threads, int inst>
class __default_alloc_template {

private:
    //将bytes上调至8的倍数
    static size_t ROUND_UP(size_t bytes) {
        return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
    }
private:
    //free-list
    union obj {
        union obj * free_list_link;
        char client_data[1];    /* The client sees this.        */
    };
private:
    //16个free-list
    static obj * volatile free_list[__NFREELISTS]; 
    //根据区块大小，决定使用第n号free-list。n从0算起
    static  size_t FREELIST_INDEX(size_t bytes) {
        return (((bytes) + __ALIGN-1)/__ALIGN - 1);
    }

    //返回一个大小为n的对象，并可能加入大小为n的其它区块到free-list
    static void *refill(size_t n);
    //分配一大块空间，可容纳nobjs个大小为”size“的区块
    //如果分配nobjs个区块有所不便，nobjs可能会降低
    static char *chunk_alloc(size_t size, int &nobjs);

    // Chunk allocation state.
    static char *start_free;  //内存池起始位置。只在chunk_alloc()中变化
    static char *end_free;    //内存池结束位置。只在chunk_alloc()中变化
    static size_t heap_size;

public:
    static void * allocate(size_t n){ /*详述于后*/ }
    static void deallocate(void *p, size_t n){ /*详述于后*/ }
    static void * reallocate(void *p, size_t old_sz, size_t new_sz);
};

/*以下是static data member的定义与初始值*/

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::start_free = 0;

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;

template <bool threads, int inst>
__default_alloc_template<threads, inst>::obj * volatile
__default_alloc_template<threads, inst> ::free_list[__NFREELISTS] = 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
```

* 空间分配函数[allocate()](tass-sgi-stl-2.91.57-source/stl_alloc.h#L403)
    - 若区块大于128bytes，就调用第一级分配器
    - 若区块小于128bytes，检查对于的free-list
        + 若free-list之内有可用的区块，则直接使用
        + 若free-list之内没有可用区块，将区块大小调至8倍数边界，调用refill()，准备为free-list重新填充空间

<div align="center"> <img src="../pic/stl-2-7.png"/> </div>

 * 空间释放函数[deallocate()](tass-sgi-stl-2.91.57-source/stl_alloc.h#L433)
     - 若区块大于128bytes，就调用第一级分配器
     - 若区块小于128bytes，找出对应的free-list，将区块回收
     
<div align="center"> <img src="../pic/stl-2-8.png"/> </div>

* 重新填充free-list的函数[refill()](tass-sgi-stl-2.91.57-source/stl_alloc.h#L537)
    - 若free-list中没有可用区块时，会调用chunk_alloc从内存池中申请空间重新填充free-list。缺省申请20个新节点(新区块)，如果内存池空间不足，获得的节点数可能小于20

* [chunk_alloc()](tass-sgi-stl-2.91.57-source/stl_alloc.h#L465)函数从内存池申请空间，根据end_free-start_free判断内存池中剩余的空间
    - 如果剩余空间充足
        + 直接调出20个区块返回给free-list
    - 如果剩余空间不足以提供20个区块，但足够供应至少1个区块
        + 拨出这不足20个区块的空间
    - 如果剩余空间连一个区块都无法供应
        + 利用malloc()从heap中分配内存（大小为需求量的2倍，加上一个随着分配次数增加而越来越大的附加量），为内存池注入新的可用空间（**详细例子见下图**）
        + 如果malloc()获取失败，chunk_alloc()就四处寻找有无”尚有未用且区块足够大“的free-list。找到了就挖出一块交出
        + 如果上一步仍为成果，那么就调用第一级分配器，第一级分配器有out-of-memory处理机制，或许有机会释放其它的内存拿来此处使用。如果可以，就成功，否则抛出bad_alloc异常
    
    <div align="center"> <img src="../pic/stl-2-9.png"/> </div>

    上图中，一开始就调用chunk_alloc(32,20)，于是malloc()分配40个32bytes区块，其中第1个交出，另19个交给free-list[3]维护，余20个留给内存池；接下来客户调用chunk_alloc(64,20)，此时free_list[7]空空如也，必须向内存池申请。内存池只能供应(32\*20)/64=10个64bytes区块，就把这10个区块返回，第1个交给客户，余9个由free_list[7]维护。此时内存池全空。接下来再调用chunk_alloc(96,20)，此时free-list[11]空空如也，必须向内存池申请。而内存池此时也为空，于是以malloc()分配40+n(附加量)个96bytes区块，其中第1个交出，另19个交给free-list[11]维护，余20+n(附加量)个区块留给内存池...

### 3.3 内存基本处理工具

STL定义了5个全局函数，作用于未初始化空间上，有助于容器的实现：

* 作用于单个对象（见[3.1 对象构造与析构](#31-对象构造与析构)，SGI STL定义在头文件[<stl_construct.h>](tass-sgi-stl-2.91.57-source/stl_construct.h)中）
    - construct()函数（构造单个对象）
    - destroy()函数（析构单个对象）
* 作用于容器的区间（本节，SGI STL定义在头文件[<stl_uninitialized.h>](tass-sgi-stl-2.91.57-source/stl_uninitialized.h)中，是高层copy()、fill()、fill_n()的底层函数）
    - [uninitialized_copy()](tass-sgi-stl-2.91.57-source/stl_uninitialized.h#L76)函数
    - [uninitialized_fill()](tass-sgi-stl-2.91.57-source/stl_uninitialized.h#L171)函数
    - [uninitialized_fill_n()](tass-sgi-stl-2.91.57-source/stl_uninitialized.h#L218)函数

容器的全区间构造函数通常分2步：

1. 分配内存区块，足以包含范围内的所有元素
2. 调用上述3个函数在全区间范围内构造对象（因此，这3个函数使我们能够将内存的分配与对象的构造行为分离；并且3个函数都具有”commit or rollback“语意，要么所有对象都构造成功，要么一个都没有构造）

<div align="center"> <img src="../pic/stl-2-10.png"/> </div>

<br>

# 三.迭代器与traits编程技法

## 1.迭代器相应类型

在算法中运用迭代器时，很可能会用到其相应类型。所谓相应类型，迭代器所指之物的类型便是其中之一，算法可以在函数体中使用迭代器所指之物的类型来定义变量，也可能将迭代器所指之物的类型作为算法的返回值：

<div align="center"> <img src="../pic/stl-3-1.png"/> </div>

* **在函数体中使用迭代器所指之物的类型**
    - C++支持sizeof()，但并未支持typeof()。即便动用RTTI性质中的typeid()，获得的也只是类型名称，不能拿来做变量声明
    - 这里利用函数模板的参数推导机制解决。算法func()作为对外接口，算法的所有逻辑另外封装在一个实现函数func_impl()中，由于它是一个函数模板，一旦被调用，编译器就会自动进行参数推导，导出类型T
* **迭代器所指之物的类型作为算法的返回类型**
    - 函数模板的参数推导机制推导的是参数，无法推导函数的返回类型
    - 这里使用嵌套类型声明解决。但是，对于类类型的迭代器，可以正常工作，但是**非类类型的原生指针无法处理**

通过上图，可以了解到在算法中对迭代器相应类型的需求。除了迭代器所指之物的类型(value type)，迭代器相应类型还包括另外4种，在traits编程技法中将会介绍，并且会提到如何使用traits来解决上面的问题（这也是STL中实际使用的方法）

## 2.traits编程技法

上一节所使用的方法，在value type作为返回类型时，无法处理非类类型的原生指针。下图使用traits来解决，使用了模板偏特化来处理非类类型的原生指针：

<div align="center"> <img src="../pic/stl-3-2.png"/> </div>

<br>

现在，不论面对的是迭代器MyIter，或是原生指针int\*或const int\*，都可以通过traits取出正确的value type

<div align="center"> <img src="../pic/stl-3-3.png"/> </div>

> 当然，若要“特性萃取机”traits能够有效运作，每一个迭代器必须遵循约定，自行以内嵌类型定义的方式定义出相应类型。这是一个约定，谁不遵守这个约定，谁就不能兼容于STL这个大家庭

**根据经验，最常用到的迭代器相应类型有5种**：

1. **value type**：指迭代器所指对象的类型
2. **difference type**：用以表示两个迭代器之间的距离
3. **pointer**：如果value type是T，那么pointer就是指向T的指针
4. **reference**：如果value type是T，那么reference就是T的引用
5. **iterator category**：迭代器的类型（[详见](#21-迭代器类型)）

    <div align="center"> <img src="../pic/stl-3-4.png"/> </div>

如果希望开发的容器能与STL相容，一定要为容器定义这5种相应类型。“特性萃取机”traits会很忠实地将特性萃取出来：

```c++
template <class Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category   iterator_category;
    typedef typename Iterator::value_type          value_type;
    typedef typename Iterator::difference_type     difference_type;
    typedef typename Iterator::pointer             pointer;
    typedef typename Iterator::reference           reference;
};
```

iterator_traits必须针对传入的类型为pointer及pointer-to-const者设计偏特化版本：

```c++
//以C++内建的ptrdiff_t（定义于<cstddef>头文件）作为原生指针的difference type

//针对原生指针的偏特化版本
template <class T>
struct iterator_traits<T*>{
    //原生指针是一种Random Access Iterator
    typedef random_access_iterator_tag   iterator_category;
    typedef T                            value_type;
    typedef ptrdiff_t                    difference_type;
    typedef T*                           pointer;
    typedef T&                           reference;
};

//针对原生pointer-to-const的偏特化版本
template <class T>
struct iterator_traits<const T*>{
    //原生指针是一种Random Access Iterator
    typedef random_access_iterator_tag   iterator_category;
    typedef T                            value_type;
    typedef ptrdiff_t                    difference_type;
    typedef const T*                     pointer;
    typedef const T&                     reference;
};
```

STL提供以下函数，简化迭代器相应类型的萃取：

```c++
//这个函数可以很方便地萃取category
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
  typedef typename iterator_traits<Iterator>::iterator_category category;
  return category();
}

//这个函数可以很方便地萃取distance type
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

//这个函数可以很方便地萃取value type
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
  return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}
```

### 2.1 迭代器类型

设计算法时，如果可能，尽量针对某种迭代器提供一个明确定义，并针对更强化的某种迭代器提供另一种定义，这样才能在不同情况下提供最大效率，如下图的advanced()函数，用于移动迭代器：

<div align="center"> <img src="../pic/stl-3-5.png"/> </div>

在上图中，每个__advance()的最后一个参数都只声明类型，并未指定参数名称，因为它纯粹只是用来激活重载机制，函数之中根本不使用该参数。如果加上参数名称也没有错，但是没必要

将advance()中的iterator_category(i)展开得到iterator_traits\<InputIterator\>::iterator_category()，这会产生一个临时对象，其类型隶属于几种迭代器中的一种。然后，根据这个类型，编译器才决定调用哪一个__advance()重载函数

**上图以class来定义迭代器的各种分类标签，有下列好处**：

* 可以促成重载机制的成功运作
* **通过继承，可以不必再写“单纯只做传递调用”的函数（如__advance()的Forward Iterator版只是单纯的调用Input Iterator版，因此可以省略）,可以通过[这个例子](stlbookcode/c3/3tag-test.cpp)来模拟证实**


## 3.std::iterator的保证

为了符合规范，任何迭代器都应该提供5个内嵌相应类型，以便于traits萃取，否则便是自别于整个STL架构，可能无法与其它STL组件顺利搭配。然而，写代码难免会有遗漏。因此，STL提供了一个iterators class如下，如果每个新设计的迭代器都继承自它，就可保证符合STL所需的规范；

```c++
template <class Category,
          class T,
          class Distance = ptrdiff_t,
          class Pointer = T*,
          class Reference = T&>
struct iterator{
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
};
```

iterator class不含任何成员，存粹只是类型定义，所以继承它不会导致任何额外负担。由于后3个参数皆有默认值，故新的迭代器只需提供前2个参数即可。以下为一个继承示例：

```c++
template <class Item>
struct ListIter : public std::iterator<std::forword_iterator_tag, Item>{
    ...
};
```

## 4.SGI STL的__type_traits

SGI将STL的traits进一步扩大到迭代器以外，于是有了所谓的__type_traits，它属于SGI STL，不属于STL标准规范

* iterator_traits：负责萃取迭代器的特性
* __type_traits：负责萃取类型的特性，包括：
    - 该类型是否具备non-trivial defalt ctor
    - 该类型是否具备non-trivial copt ctor
    - 该类型是否具备non-trivial assignment operator
    - 该类型是否具备non-trivial dtor

通过使用__type_traits，在对某个类型进行构造、析构、拷贝、赋值等操作时，就可以采用最有效率的措施。这对于大规模而操作频繁的容器，有着显著的效率提升

萃取类型的特性时，我们希望得到一个”真“或”假“（以便决定采取什么策略），但其结果不应该只是个bool值，应该是个有着真/假性质的”对象”，因为我们希望利用响应的结果来进行参数推导，而编译器只有面对class object形式的参数，才会做参数推导，所以萃取类型的特性时，返回__true_type或__false_type：

```c++
struct __true_type { };
struct __false_type { };
```

模板类__type_traits的泛化与特化/偏特化见下图：

<div align="center"> <img src="../pic/stl-3-5.png"/> </div>

<br>

# 四.顺序容器

<div align="center"> <img src="../pic/stl-4-1.jpeg"/> </div>

上图中的“衍生”并非“派生”，而是内含关系。例如heap内含一个vector，priority-queue内含一个heap，stack和queue都含一个deque，set/map/multiset/multimap都内含一个RB-tree，has_x都内含一个hashtable

## 1.vector

array是静态空间，一旦配置了就不能改变；vector与array非常相似，但是vector是动态空间，随着元素的加入，内部机制会自动扩充以容纳新元素

SGI STL中[vector的定义](tass-sgi-stl-2.91.57-source/stl_vector.h#L12)

<div align="center"> <img src="../pic/stl-4-2.png"/> </div>

### 1.1 迭代器

vector维护的是一个连续线性空间，所以不论其元素类型为何，普通指针都可以作为vector的迭代器而满足所有必要条件，因为vector迭代器所需要的操作行为，如operator\*，operator->，operator++，operator--，operator+，operator-，operator+=，operator-=，普通指针天生就具备。vector支持随机存取，而普通指针正有着这样的能力。所以，vector提供的是Random Access Iterators：

```c++
template <class T,class Alloc = alloc>
class vector{
public:
    typedef T               value_type;
    typedef value_type*     iterator;   //vector的迭代器时普通指针
...
};
```

### 1.2 分配器

vector缺省使用alloc作为空间分配器，并据此另外定义了一个data_allocator，为的是更方便以元素大小为配置单位：

```c++
template<class T,class Alloc = alloc>
class vector{
protected:
    typedef simple_alloc<value_type,Alloc> data_allocator;
...
};
```

因此，data_allocator::allocate(n)表示分配n个元素空间

### 1.3 vector操作的实现

常见的vector操作包括：

* [vector(size_type n,const T &value)](tass-sgi-stl-2.91.57-source/stl_vector.h#L98)
    - [fill_initialize(size_type n,const T &value)](tass-sgi-stl-2.91.57-source/stl_vector.h#L98)
        + [allocate_and_fill(size_type n, const T& x)](tass-sgi-stl-2.91.57-source/stl_vector.h#L213)
* [push_back(const T &x)](tass-sgi-stl-2.91.57-source/stl_vector.h#L144)
    - [insert_aux(iterator position,const T &x)](tass-sgi-stl-2.91.57-source/stl_vector.h#L323)
* [pop_back()](tass-sgi-stl-2.91.57-source/stl_vector.h#L186)
* [erase(iterator first, iterator last)](tass-sgi-stl-2.91.57-source/stl_vector.h#L197)
* [erase(iterator position)](tass-sgi-stl-2.91.57-source/stl_vector.h#L190)
* [insert(iterator position, size_type n, const T& x)](tass-sgi-stl-2.91.57-source/stl_vector.h#L361)

**插入操作可能造成vector的3个指针重新配置，导致原有的迭代器全部失效**

## 2.list

SGI STL中[list的定义](tass-sgi-stl-2.91.57-source/stl_list.h#L124)

### 2.1 节点

<div align="center"> <img src="../pic/stl-4-3.png"/> </div>

```c++
template <class T>
struct __list_node{
    typedef void* void_pointer;
    void_pointer prev;  //类型为void*
    void_pointer next;
};
```

### 2.2 迭代器

list不再能够像vector一样以普通指针作为迭代器，因为其节点不保证在存储空间中连续存在

list迭代器必须有能力指向list的节点，并有能力进行正确的递增、递减、取值、成员存取等操作。list中，迭代器与节点的关系见下图：

<div align="center"> <img src="../pic/stl-4-4.png"/> </div>

由于STL list是一个双向链表，迭代器必须具备前移、后移的能力，所以list提供的是Bidirectional Iterators

**list的插入和接合操作都不会造成原有的list迭代器失效，对于删除操作，也只有”指向被删除元素“的那个迭代器失效，其它迭代器不受任何影响**

```c++
template<class T, class Ref, class Ptr>
struct __list_iterator {
  typedef __list_iterator<T, T&, T*>             iterator;
  typedef __list_iterator<T, const T&, const T*> const_iterator;
  typedef __list_iterator<T, Ref, Ptr>           self;

  typedef bidirectional_iterator_tag iterator_category;
  typedef T value_type;
  typedef Ptr pointer;
  typedef Ref reference;
  typedef __list_node<T>* link_type;//节点指针类型link_type
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  link_type node;//迭代器内部的指针，指向list的节点

  __list_iterator(link_type x) : node(x) {}
  __list_iterator() {}
  __list_iterator(const iterator& x) : node(x.node) {}

  bool operator==(const self& x) const { return node == x.node; }
  bool operator!=(const self& x) const { return node != x.node; }
  //对迭代器取值，取的是节点的数据值
  reference operator*() const { return (*node).data; }

#ifndef __SGI_STL_NO_ARROW_OPERATOR
  //以下是迭代器的成员存取运算子的标准做法
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  //对迭代器累加1，就是前进一个节点
  self& operator++() { 
    node = (link_type)((*node).next);
    return *this;
  }
  self operator++(int) { 
    self tmp = *this;
    ++*this;
    return tmp;
  }

  //对迭代器递减1，就是后退一个节点
  self& operator--() { 
    node = (link_type)((*node).prev);
    return *this;
  }
  self operator--(int) { 
    self tmp = *this;
    --*this;
    return tmp;
  }
};
```

### 2.3 list的数据结构

SGI list不仅是一个双向链表，还是一个环状双向链表。所以它只需要一个指针，便可完整表现整个链表：

```c++
template <class T, class Alloc = alloc>
class list {
protected:
    typedef __list_node<T> list_node;
public:
    typedef list_node* link_type;

protected:
    link_type node; //只要一个指针，便可表示整个环状双向链表
};

iterator begin() { return (link_type)((*node).next); }
iterator end() { return node; }
size_type size() const {
    size_type result = 0;
    distance(begin(), end(), result);
    return result;
}
```

<div align="center"> <img src="../pic/stl-4-5.png"/> </div>

### 2.4 分配器

list缺省使用alloc作为空间分配器，并据此另外定义了一个list_node_allocator，为的是更方便以节点大小为配置单位：

```c++
template <class T, class Alloc = alloc>
class list {
protected:
    typedef simple_alloc<list_node, Alloc> list_node_allocator;
...
};
```

因此，list_node_allocator::allocate(n)表示分配n个节点空间

### 2.5 list操作的实现

* 节点操作
    - 分配一个节点：[get_node](tass-sgi-stl-2.91.57-source/stl_list.h#L156)
    - 释放一个节点：[put_node](tass-sgi-stl-2.91.57-source/stl_list.h#L157)
    - 生成（分配并构造）一个节点：[create_node](tass-sgi-stl-2.91.57-source/stl_list.h#L159)
    - 销毁（析构并释放）一个节点：[destroy_node](tass-sgi-stl-2.91.57-source/stl_list.h#L167)
    - 节点插入：[push_back](tass-sgi-stl-2.91.57-source/stl_list.h#L269)和[push_front](tass-sgi-stl-2.91.57-source/stl_list.h#L268)
        + [insert](tass-sgi-stl-2.91.57-source/stl_list.h#L243)
    - 节点移除：[erase](tass-sgi-stl-2.91.57-source/stl_list.h#L270),[pop_front](tass-sgi-stl-2.91.57-source/stl_list.h#L283)和[pop_back](tass-sgi-stl-2.91.57-source/stl_list.h#L284)
    - 移除某一数值的所有节点：[remove](tass-sgi-stl-2.91.57-source/stl_list.h#L468)
    - 移除数值相同的连续节点：[unique](tass-sgi-stl-2.91.57-source/stl_list.h#L480)
* 链表操作
    - 创建一个空链表：[list()](tass-sgi-stl-2.91.57-source/stl_list.h#L217)
        + [empty_initialize](tass-sgi-stl-2.91.57-source/stl_list.h#L173)
    - 链表清空：[clear](tass-sgi-stl-2.91.57-source/stl_list.h#L438)
* 链表拼接：[splice](tass-sgi-stl-2.91.57-source/stl_list.h#L328)
    - 将[first,last)内的元素移动到position之前：[transfer](tass-sgi-stl-2.91.57-source/stl_list.h#L315)（[first,last)区间可以在同一个list之中，transfer并非公开接口，公开的是splice）
    
    <div align="center"> <img src="../pic/stl-4-6.png"/> </div>

## 3.deque

deque是一种双向开口的连续线性空间

deque和vector最大的差异：

1. deque允许于常数时间内对起头端进行元素的插入或移除操作
2. deque没有所谓容量观念，因为它是动态地以分段连续空间组合而成，随时可以增加一段新的空间并链接起来（deque没有必要提供所谓的空间保留功能）

### 3.1 迭代器

deque是分段连续空间。维持其”整体连续“假象的任务，落在了迭代器的operator++和operator--两个云算子身上

deque迭代器必须能够指出分段连续空间（即缓冲区）在哪；必须能够判断自己是否已经处于其所在缓冲器的边缘。为了能够正确跳跃，迭代器必须随时掌握中控器map

```c++
template <class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {   //未继承std::iterator
  typedef __deque_iterator<T, T&, T*, BufSiz>             iterator;
  typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
  static size_t buffer_size() {return __deque_buf_size(BufSiz, sizeof(T)); }

  //为继承std::iterator，所以必须自行撰写5个必要的迭代器相应类型
  typedef random_access_iterator_tag iterator_category; // (1)
  typedef T value_type;                                 // (2)
  typedef Ptr pointer;                                  // (3)
  typedef Ref reference;                                // (4)
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;                    // (5)
  typedef T** map_pointer;

  typedef __deque_iterator self;

  //保持与容器的联结
  T* cur;           //此迭代器所指缓冲区中的当前元素
  T* first;         //此迭代器所指缓冲区的头
  T* last;          //此迭代器所指缓冲区的尾(含备用空间)
  map_pointer node; //指向中控器map
...
};
```

迭代器操作：

* 更新迭代器指向的缓冲区：set_node
* [解引用\*](tass-sgi-stl-2.91.57-source/stl_deque.h#L130) 
* [成员选择->](tass-sgi-stl-2.91.57-source/stl_deque.h#L132)
* [迭代器相减-](135)
* [前置++](tass-sgi-stl-2.91.57-source/stl_deque.h#L140)和[后置++](tass-sgi-stl-2.91.57-source/stl_deque.h#L148)
* [前置--](tass-sgi-stl-2.91.57-source/stl_deque.h#L154)和[后置--](tass-sgi-stl-2.91.57-source/stl_deque.h#L162)
* 复合赋值[+=](tass-sgi-stl-2.91.57-source/stl_deque.h#L168)和[-=](tass-sgi-stl-2.91.57-source/stl_deque.h#L187)
* 迭代器[+n](tass-sgi-stl-2.91.57-source/stl_deque.h#L182)和[-n](tass-sgi-stl-2.91.57-source/stl_deque.h#L189)
* 随机存取[\[\]](tass-sgi-stl-2.91.57-source/stl_deque.h#L194)
* 相等判断[==](tass-sgi-stl-2.91.57-source/stl_deque.h#L196)，[!=](tass-sgi-stl-2.91.57-source/stl_deque.h#L197)和[<](tass-sgi-stl-2.91.57-source/stl_deque.h#L198)

### 3.3 deque的数据结构

deque采用一块所谓的map作为**主控(中控器)**。这里所谓的map是指一小块连续空间，其中每个元素都是一个指针，指向另一段（较大的）连续线性空间，称为缓冲区。缓冲区才是deque的存储空间主体。SGI STL允许我们指定缓冲区大小，默认值0表示使用512bytes缓冲区

<div align="center"> <img src="../pic/stl-4-7.png"/> </div>

deque除了维护一个指向map的指针外，也维护start，finish两个迭代器。分别指向第一缓冲区的第一个元素和最后缓冲区的最后一个元素（的下一位置）。此外，也必须记住目前的map大小。因为一旦map所提供的节点不足，就必须重新配置更大的一块map

```c++
temlate <class T,class Alloc = alloc,size_t BufSiz = 0>
class deque{
public:     //Basic types
    typedef T value_type;
    typedef value_type* pointer;
    typedef size_t size_type;
    ...

public:
    typedef __deque_iterator<T,T&.T*,BufSiz> iterator;  //迭代器类型

protected:  //Internal typedefs
    //元素的指针的指针
    typedef pointer* map_pointer;

protected:  //Data members
    iterator start;         //第一个节点的迭代器
    iterator finish;        //最后一个节点的迭代器

    map_pointer map;        //指向map，map是块连续空间
                            //其每个元素都是个指针，指向一个节点(缓冲区)
    size_type map_size;     //map的大小，即内有多少个指针
...
};
```

deque的中控器、缓冲区、迭代器的关系如下图：

<div align="center"> <img src="../pic/stl-4-8.png"/> </div>

### 3.4 分配器

deque自行定义了2个专属的空间配置器：

```c++
protected:
    //专属的空间分配器，每次分配一个元素大小
    typedef simple_alloc<value_type,Alloc> data_allocator;
    //专属的空间分配器，每次分配一个指针大小
    typedef simple_alloc<pointer,Alloc> map_allocator;
```

### 3.5 deque操作的实现

* deque构造与初始化：[deque](tass-sgi-stl-2.91.57-source/stl_deque.h#L360)
    - 元素初始化[fill_initialize](tass-sgi-stl-2.91.57-source/stl_deque.h#L847)
        + 空间分配与成员设定[create_map_and_nodes](tass-sgi-stl-2.91.57-source/stl_deque.h#L797)
* 插入操作：
    - 在队列末尾插入：[push_back](tass-sgi-stl-2.91.57-source/stl_deque.h#L439)
        + 最后缓冲区只有1个可用空间时：[push_back_aux](tass-sgi-stl-2.91.57-source/stl_deque.h#L898)
            * map不足时：[reserve_map_at_back](tass-sgi-stl-2.91.57-source/stl_deque.h#L632)
                - [reallocate_map](tass-sgi-stl-2.91.57-source/stl_deque.h#L1289)
    - 在队列首部插入：[push_front](tass-sgi-stl-2.91.57-source/stl_deque.h#L448)
        + 第一个缓冲区没有可用空间时：[push_front_aux](tass-sgi-stl-2.91.57-source/stl_deque.h#L912)
            * map不足时：[reserve_map_at_front](tass-sgi-stl-2.91.57-source/stl_deque.h#L639)
                - [reallocate_map](tass-sgi-stl-2.91.57-source/stl_deque.h#L1289)
    - 指定位置插入一个元素：[insert](tass-sgi-stl-2.91.57-source/stl_deque.h#L447)
        + 在首部插入：push_front
        + 在尾部插入：push_back
        + 在中间插入：[insert_aux](tass-sgi-stl-2.91.57-source/stl_deque.h#L994)
* 弹出操作：
    - 弹出队列末尾元素：[pop_back](tass-sgi-stl-2.91.57-source/stl_deque.h#L457)
        + 最后缓冲区没有元素时：[pop_back_aux](tass-sgi-stl-2.91.57-source/stl_deque.h#L933)
    - 弹出队列首部元素：[pop_front](tass-sgi-stl-2.91.57-source/stl_deque.h#L466)
        + 第一个缓冲区仅有一个元素时：[pop_front_aux](tass-sgi-stl-2.91.57-source/stl_deque.h#L945)
* 清除所有元素：[clear](tass-sgi-stl-2.91.57-source/stl_deque.h#L774)
* 清除某个区间的元素：[erase](tass-sgi-stl-2.91.57-source/stl_deque.h#L743)

## 4.stack

具有”修改某物接口，形成另一种风貌“的性质者，称为适配器。因此，STL stack往往不被归类为容器，而被归类为容器适配器

SGI STL以deque作为缺省情况下的stack底部结构，定义如下：

```c++
template <class T, class Sequence = deque<T> >
class stack {
  //以下__STL_NULL_TMPL_ARGS会展开为 <>
  friend bool operator== __STL_NULL_TMPL_ARGS (const stack&, const stack&);
  friend bool operator< __STL_NULL_TMPL_ARGS (const stack&, const stack&);
public:
  typedef typename Sequence::value_type value_type;
  typedef typename Sequence::size_type size_type;
  typedef typename Sequence::reference reference;
  typedef typename Sequence::const_reference const_reference;
protected:
  Sequence c;   //底层容器
public:
  //以下完全利用Sequence c的操作，完成stack的操作
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference top() { return c.back(); }
  const_reference top() const { return c.back(); }
  //deque是两头可进出，stack是后进后出
  void push(const value_type& x) { c.push_back(x); }
  void pop() { c.pop_back(); }
};

template <class T, class Sequence>
bool operator==(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
  return x.c == y.c;
}

template <class T, class Sequence>
bool operator<(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
  return x.c < y.c;
}
```

只有stack顶端的元素有机会被外界取用，stack不提供遍历功能，也**不提供迭代器**

**指定其它容器作为stack的底层容器的方法：**

```c++
stack<int,list<int> > istack;
```

## 5.queue

queue（队列）是一种先进先出的数据结构，尾端插入，首部移出

SGI STL以deque作为缺省情况下的queue底部结构，定义如下：

```c++
template <class T, class Sequence = deque<T> >
class queue {
  //以下__STL_NULL_TMPL_ARGS会展开为 <>
  friend bool operator== __STL_NULL_TMPL_ARGS (const queue& x, const queue& y);
  friend bool operator< __STL_NULL_TMPL_ARGS (const queue& x, const queue& y);
public:
  typedef typename Sequence::value_type value_type;
  typedef typename Sequence::size_type size_type;
  typedef typename Sequence::reference reference;
  typedef typename Sequence::const_reference const_reference;
protected:
  Sequence c;   //底层容器
public:
  //以下完全利用Sequence c的操作，完成stack的操作
  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference front() { return c.front(); }
  const_reference front() const { return c.front(); }
  reference back() { return c.back(); }
  const_reference back() const { return c.back(); }
  deque是两头可进出，queue是尾端紧、首部出
  void push(const value_type& x) { c.push_back(x); }
  void pop() { c.pop_front(); }
};

template <class T, class Sequence>
bool operator==(const queue<T, Sequence>& x, const queue<T, Sequence>& y) {
  return x.c == y.c;
}

template <class T, class Sequence>
bool operator<(const queue<T, Sequence>& x, const queue<T, Sequence>& y) {
  return x.c < y.c;
}
```

只有首部元素才有机会被外界取用，queue不提供遍历功能，也**不提供迭代器**

**指定其它容器作为queue的底层容器的方法：**

```c++
queue<int,list<int> > iqueue;
```

## 6.heap

heap并不归属与STL容器组件，它是个幕后英雄，扮演priority queue的助手

heap是一颗完全二叉树，完全二叉树使用数组实现，因此使用一个vector作为heap的结构，然后通过一组xxx_heap算法，使其符合heap的性质

* 上溯（在此之前应该push_back）：[push_heap](tass-sgi-stl-2.91.57-source/stl_heap.h#L60)
    - [__push_heap_aux](tass-sgi-stl-2.91.57-source/stl_heap.h#L53)
        + [__push_heap](tass-sgi-stl-2.91.57-source/stl_heap.h#L40)
    
    <div align="center"> <img src="../pic/stl-4-13.png"/> </div>

* [pop_heap](tass-sgi-stl-2.91.57-source/stl_heap.h#L124)（在此之后应该pop_back）
    - [__pop_heap_aux](tass-sgi-stl-2.91.57-source/stl_heap.h#L118)
        + [__pop_heap](tass-sgi-stl-2.91.57-source/stl_heap.h#L110)
            * [__adjust_heap](tass-sgi-stl-2.91.57-source/stl_heap.h#L91)
    
    <div align="center"> <img src="../pic/stl-4-12.png"/> </div>

* [sort_heap](tass-sgi-stl-2.91.57-source/stl_heap.h#L209)
    
    <div align="center"> <img src="../pic/stl-4-11.png"/> </div>

* [make_heap](tass-sgi-stl-2.91.57-source/stl_heap.h#L203)
    - [__make_heap](tass-sgi-stl-2.91.57-source/stl_heap.h#L189)

## 7.priority_queue

顾名思义，priority_queue就是具有优先级的queue，允许首部移出，尾端插入。缺省情况下利用一个max-heap完成，因此首部元素优先级最高

以下为SGI STL中priority_queue的定义：

```c++
template <class T, class Sequence = vector<T>, 
          class Compare = less<typename Sequence::value_type> >
class  priority_queue {
public:
  typedef typename Sequence::value_type value_type;
  typedef typename Sequence::size_type size_type;
  typedef typename Sequence::reference reference;
  typedef typename Sequence::const_reference const_reference;
protected:
  Sequence c;       //底层容器
  Compare comp;     //元素大小比较标准
public:
  priority_queue() : c() {}
  explicit priority_queue(const Compare& x) :  c(), comp(x) {}

  //以下用到的make_heap()、push_heap()、pop_heap()都是泛型算法
  //构造一个priority queue，首先根据传入的迭代器区间初始化底层容器c，然后调用
  //make_heap()使用底层容器建堆
  template <class InputIterator>
  priority_queue(InputIterator first, InputIterator last, const Compare& x)
    : c(first, last), comp(x) { make_heap(c.begin(), c.end(), comp); }
  template <class InputIterator>
  priority_queue(InputIterator first, InputIterator last) 
    : c(first, last) { make_heap(c.begin(), c.end(), comp); }

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  const_reference top() const { return c.front(); }
  void push(const value_type& x) {
    //先利用底层容器的push_back()将新元素推入末端，再重排heap
    __STL_TRY {
      c.push_back(x); 
      push_heap(c.begin(), c.end(), comp);
    }
    __STL_UNWIND(c.clear());
  }
  void pop() {
    //从heap内取出一个元素。但不是真正弹出，而是重排heap，然后以底层容器的pop_back()
    //取得被弹出的元素
    __STL_TRY {
      pop_heap(c.begin(), c.end(), comp);
      c.pop_back();
    }
    __STL_UNWIND(c.clear());
  }
};
```

和queue一样，priority queue只有首部的元素有机会被外界取用。不提供遍历功能，也**不提供迭代器**

## 8.slist

slist**并不在标准规格之内**，由SGI STL提供，slist和list不同的是slist是单链表

单链表每个节点的消耗更小，但是只支持单向遍历，所以功能会受到许多限制

SGI STL中[slist的定义](tass-sgi-stl-2.91.57-source/stl_slist.h#L175)

### 8.1 slist的节点

<div align="center"> <img src="../pic/stl-4-9.png"/> </div>

节点相关的结构：

```c++
//单向链表的节点基本结构
struct __slist_node_base
{
    __slist_node_base *next;
};

//单向链表的节点结构
template <class T>
struct __slist_node : public __slist_node_base
{
    T data;
}
```

节点相关的全局函数：

```c++
//已知某一节点prev_node，将新节点new_node插入其后
inline __slist_node_base* __slist_make_link(
    __slist_node_base *prev_node,
    __slist_node_base *new_node)
{
    //令new节点的下一节点为prev节点的下一节点
    new_node->next = prev_node->next;
    prev_node->next = new_node; //令prev节点的下一节点指向new节点
    return new_node;
}

//单向链表的大小（元素个数）
inline size_t __slist_size(__slist_node_base *node)
{
    size_t result = 0;
    for(;node != 0;node = node->next)
        ++result;   //一个个累计
    return result;
}
```

### 8.2 slist的迭代器

<div align="center"> <img src="../pic/stl-4-10.png"/> </div>

迭代器的定义如下：

```c++
//单向链表的迭代器基本结构
struct __slist_iterator_base
{
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef forward_iterator_tag iterator_category;   //单向

  __slist_node_base* node;  //指向节点基本结构

  __slist_iterator_base(__slist_node_base* x) : node(x) {}

  void incr() { node = node->next; }    //前进一个节点

  bool operator==(const __slist_iterator_base& x) const {
    return node == x.node;
  }
  bool operator!=(const __slist_iterator_base& x) const {
    return node != x.node;
  }
};

//单向链表的迭代器结构
template <class T, class Ref, class Ptr>
struct __slist_iterator : public __slist_iterator_base
{
  typedef __slist_iterator<T, T&, T*>             iterator;
  typedef __slist_iterator<T, const T&, const T*> const_iterator;
  typedef __slist_iterator<T, Ref, Ptr>           self;

  typedef T value_type;
  typedef Ptr pointer;
  typedef Ref reference;
  typedef __slist_node<T> list_node;

  __slist_iterator(list_node* x) : __slist_iterator_base(x) {}
  __slist_iterator() : __slist_iterator_base(0) {}
  __slist_iterator(const iterator& x) : __slist_iterator_base(x.node) {}

  reference operator*() const { return ((list_node*) node)->data; }
  pointer operator->() const { return &(operator*()); }

  self& operator++()
  {
    incr(); //前进一个节点
    return *this;
  }
  self operator++(int)
  {
    self tmp = *this;
    incr(); //前进一个节点
    return tmp;
  }
};
```

<br>

# 五.关联容器

<div align="center"> <img src="../pic/stl-4-1.jpeg"/> </div>

标准的STL关联容器分为set(集合)和map(映射表)两大类，以及这两大类的衍生体multiset(多键集合)和multimap(多键映射表)。这些容器的底层机制均以RB-tree(红黑树)完成。RB-tree也是一个独立容器，但并不开放给外界使用

此外，SGI STL还提供了一个不在标准规格之列的关联容器：hash table，以及以此hash table为底层机制而完成的hash_set(散列集合)、hash_map(散列映射表)、hash_multiset(散列多键集合)、hash_multimap(散列多键映射表)

## 1.RB-tree

### 1.1 RB-tree的节点

```c++
typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;   //红色为0
const __rb_tree_color_type __rb_tree_black = true;  //黑色为1

//RB-tree节点的基类
struct __rb_tree_node_base
{
  typedef __rb_tree_color_type color_type;
  typedef __rb_tree_node_base* base_ptr;

  color_type color; //颜色
  base_ptr parent;  //指向父节点的指针
  base_ptr left;    //指向左子节点的指针
  base_ptr right;   //指向右子节点的指针

  //静态函数，获取以x为根节点的RB-tree最小节点的指针
  static base_ptr minimum(base_ptr x)
  {
    while (x->left != 0) x = x->left;
    return x;
  }

  //静态函数，获取以x为根节点的RB-tree最大节点的指针
  static base_ptr maximum(base_ptr x)
  {
    while (x->right != 0) x = x->right;
    return x;
  }
};

//RB-tree节点类
template <class Value>
struct __rb_tree_node : public __rb_tree_node_base
{
  typedef __rb_tree_node<Value>* link_type;
  Value value_field;    //RB-tree节点的value
};
```

**键和值都包含在value_field中**

### 1.2 RB-tree的迭代器

SGI将RB-tree迭代器实现为两层：

<div align="center"> <img src="../pic/stl-5-1.jpeg"/> </div>

RB-tree迭代器属于双向迭代器，但不具备随机定位能力。前进操作operator++()调用了基类迭代器的increment()，后退操作operator--()调用了基类迭代器的decrement()。前进或后退的举止行为完全依据二叉搜索树的节点排列法则

```c++
//迭代器基类
struct __rb_tree_base_iterator
{
  typedef __rb_tree_node_base::base_ptr base_ptr;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  base_ptr node;    //节点基类类型的指针，将迭代器连接到RB-tree的节点

  void increment()
  {
    if (node->right != 0) {//如果node右子树不为空，则找到右子树的最左子节点
      node = node->right;
      while (node->left != 0)
        node = node->left;
    }
    else {//如果node右子树为空，则找到第一个“该节点位于其左子树”的节点
      base_ptr y = node->parent;
      while (node == y->right) {
        node = y;
        y = y->parent;
      }
      if (node->right != y)
        node = y;
    }
  }

  void decrement()
  {
    if (node->color == __rb_tree_red &&
        node->parent->parent == node)//这种情况发生于node为header时（亦即node为
      node = node->right;            //end()时）header右子节点即mostright，指向max节点
    else if (node->left != 0) {//如果左子树不为空，则找到左子树的最右子节点
      base_ptr y = node->left;
      while (y->right != 0)
        y = y->right;
      node = y;
    }
    else {//如果左子树为空，则找到第一个“该节点位于其右子树”的节点
      base_ptr y = node->parent;
      while (node == y->left) {
        node = y;
        y = y->parent;
      }
      node = y;
    }
  }
};

//迭代器类
template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator
{
  typedef Value value_type;
  typedef Ref reference;
  typedef Ptr pointer;
  typedef __rb_tree_iterator<Value, Value&, Value*>             iterator;
  typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
  typedef __rb_tree_iterator<Value, Ref, Ptr>                   self;
  typedef __rb_tree_node<Value>* link_type; //指向RB-tree节点的指针类型

  __rb_tree_iterator() {}
  __rb_tree_iterator(link_type x) { node = x; }
  __rb_tree_iterator(const iterator& it) { node = it.node; }

  //解引用操作为获取所指RB-tree节点的value
  reference operator*() const { return link_type(node)->value_field; }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  //调用父类的increment()，函数会修改node成员，使其指向后一个RB-tree节点
  self& operator++() { increment(); return *this; }
  self operator++(int) {
    self tmp = *this;
    increment();
    return tmp;
  }
    
  //调用父类的decrement()，函数会修改node成员，使其指向前一个RB-tree节点
  self& operator--() { decrement(); return *this; }
  self operator--(int) {
    self tmp = *this;
    decrement();
    return tmp;
  }
};
```

### 1.3 RB-tree操作的实现

SGI STL中[RB-tree的定义](tass-sgi-stl-2.91.57-source/stl_tree.h#L428)

* 节点操作：
    - 涉及内存管理的操作
        + 分配节点：[get_node](tass-sgi-stl-2.91.57-source/stl_tree.h#L447)
        + 释放节点：[put_node](tass-sgi-stl-2.91.57-source/stl_tree.h#L449)
        + 创建节点：[create_node](tass-sgi-stl-2.91.57-source/stl_tree.h#L452)
        + 拷贝节点：[clone_node](tass-sgi-stl-2.91.57-source/stl_tree.h#L462)
        + 销毁节点：[destroy_node](tass-sgi-stl-2.91.57-source/stl_tree.h#L471)
    - [获取节点成员](tass-sgi-stl-2.91.57-source/stl_tree.h#L489)：
        + left
        + right
        + parent
        + value
        + key
        + color
* RB-tree操作
    - 创建空RB-tree：[rb_tree](tass-sgi-stl-2.91.57-source/stl_tree.h#L542)
        + 初始化：[init](tass-sgi-stl-2.91.57-source/stl_tree.h#L532)
    - 获取root节点：[root](tass-sgi-stl-2.91.57-source/stl_tree.h#L485)
    - 获取最左子节点：[leftmost](tass-sgi-stl-2.91.57-source/stl_tree.h#L486)
    - 获取最右子节点：[rightmost](tass-sgi-stl-2.91.57-source/stl_tree.h#L487)
    - 获取起始节点：[begin](tass-sgi-stl-2.91.57-source/stl_tree.h#L575)
    - 获取末尾节点：[end](tass-sgi-stl-2.91.57-source/stl_tree.h#L577)
    - 是否为空：[empty](tass-sgi-stl-2.91.57-source/stl_tree.h#L587)
    - 大小：[size](tass-sgi-stl-2.91.57-source/stl_tree.h#L588)
    - **插入节点**：
        + 节点值独一无二：[insert_unique](tass-sgi-stl-2.91.57-source/stl_tree.h#L753)
            * [__insert](tass-sgi-stl-2.91.57-source/stl_tree.h#L698)
                - [__rb_tree_rebalance](tass-sgi-stl-2.91.57-source/stl_tree.h#L249)
                    + [__rb_tree_rotate_left](tass-sgi-stl-2.91.57-source/stl_tree.h#L210)
                    + [__rb_tree_rotate_right](tass-sgi-stl-2.91.57-source/stl_tree.h#L229) 
        + 允许节点值重复：[insert_equal](tass-sgi-stl-2.91.57-source/stl_tree.h#L736)
            * __insert（同上）
                - __rb_tree_rebalance（同上）
                    + __rb_tree_rotate_left（同上）
                    + __rb_tree_rotate_right（同上）
    - **元素搜索**：
        + [find](tass-sgi-stl-2.91.57-source/stl_tree.h#L964)
