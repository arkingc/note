## 1.为什么要内存对齐

1. **性能原因**：内存对齐可以提高存取效率（例如，有些平台每次读都是从偶地址开始，如果一个int型存放在偶地址开始的地方，那么一个读周期就可以读出这32bit，而如果存放在奇地址开始的地方，就需要2个读周期，并且要对两次读出的结果的高低字节进行拼凑才能得到这32bit的数据）
2. **平台原因**：各个硬件平台对存储空间的处理有很大的不同，一些平台对某些特定类型的数据只能从某些特定地址开始存取，例如，有些架构的CPU在访问一个没有对齐的变量时会发生错误，那么这时候编程必须保证字节对齐

<br>

## 2.valgrind

### 2.1 框架

<div align="center"> <img src="pic/6.png"/> </div>

vagrind包括下列一些工具：

* **Memcheck**：valgrind应用最广泛的工具，一个重量级的**内存检查**器，能够发现开发中绝大多数内存错误使用情况，**我们主要使用即此工具，默认选项**。此工具检查下面的程序错误：
    - [使用未初始化的内存](#1使用未初始化内存)(Use of uninitialised memory)
    - **使用已经释放了的内存**(Reading/writing memory after it has been free’d)
    - [使用超过malloc分配的内存空间](2内存越界访问)(Reading/writing off the endof malloc’d blocks)
    - **对堆栈的非法访问**(Reading/writing inappropriate areas on the stack)
    - **申请的空间是否有释放**(Memory leaks – where pointers to malloc’d blocks are lost forever)
    - **malloc/free/new/delete申请和释放内存的匹配**(Mismatched use of malloc/new/new \[\] vs free/delete/delete \[\])
    - [src和dst的重叠](#3内存覆盖)(Overlapping src and dst pointers inmemcpy() and related functions)
* **Callgrind**：主要用来检查程序中**函数调用过程**中出现的问题
* **Cachegrind**：它主要用来检查程序中**缓存使用**出现的问题
* **Helgrind**：它主要用来检查**多线程**程序中出现**的竞争**问题
* **Massif**：主要用来检查程序中**堆栈使用**中出现的问题
* **Extension**：可以利用core提供的功能，自己编写特定的内存调试工具

### 2.2 内存检测原理

<div align="center"> <img src="pic/6.png"/> </div>

Memcheck 能够检测出内存问题，关键在于其建立了两个全局表：

* **Valid-Value 表**：对于进程的整个地址空间中的每一个字节(byte)，都有与之对应的 8 个 bits；对于 CPU 的每个寄存器，也有一个与之对应的 bit 向量。这些 bits 负责记录该字节或者寄存器值是否具有有效的、已初始化的值
* **Valid-Address 表**：对于进程整个地址空间中的每一个字节(byte)，还有与之对应的 1 个 bit，负责记录该地址是否能够被读写

**检测原理**：

* 当要读写内存中某个字节时，首先检查这个字节对应的 A bit。如果该A bit显示该位置是无效位置，memcheck 则报告读写错误
* 内核（core）类似于一个虚拟的 CPU 环境，这样当内存中的某个字节被加载到真实的 CPU 中时，该字节对应的 V bit 也被加载到虚拟的 CPU 环境中。一旦寄存器中的值，被用来产生内存地址，或者该值能够影响程序输出，则 memcheck 会检查对应的V bits，如果该值尚未初始化，则会报告使用未初始化内存错误

### 2.3 检测步骤与示例

**步骤**：

* **1）编译源文件获取可执行程序**：为了使valgrind发现的错误更精确，如能够定位到源代码行，建议在编译时加上-g参数
    ```
    gcc -g test.c
    ```
* **2）在valgrind下，运行可执行程序**：
    - Valgrind 的参数分为两类：
        + 一类是 core 的参数，它对所有的工具都适用
        + 另外一类就是具体某个工具如 memcheck 的参数。Valgrind 默认的工具就是 memcheck，也可以通过“--tool=tool name”指定其他的工具
    ```
    valgrind [valgrind-options] program [program-options]
    ```

#### 1）使用未初始化内存

```c
#include <stdio.h>

int main()
{
    int s,i;
    printf("sum:%d\n",s);

    return 0;
}
```

程序：

![](pic/8.png)

错误信息：

![](pic/8-1.png)

#### 2）内存越界访问

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr = (int*)malloc(sizeof(int) * 4);
    arr[4] = 10;

    return 0;
}
```

程序：

![](pic/9.png)

错误信息：

![](pic/9-1.png)

#### 3）内存覆盖

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy

int main()
{
    char buf[20];

    int i;
    for(i = 1;i <= 20;i++)
        buf[i - 1] = i;

    //(dst,src,size)
    memcpy(buf + 5,buf,10);
    memcpy(buf,buf + 5,10);

    return 0;
}
```

程序：

![](pic/10.png)

错误信息：

![](pic/10-1.png)

#### 4）动态内存管理错误

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *buf = (char*)malloc(20);

    int i;
    for(i = 1;i <= 20;i++)
        buf[i - 1] = i;

    delete buf;     //1.申请与释放不匹配
    
    buf[1] = 'a';   //2.读写释放后的内存

    return 0;
}

```

程序：

![](pic/11.png)

错误信息：

![](pic/11-1.png)

#### 5）内存泄露

```c++
#include <stdio.h>
#include <stdlib.h>

struct ListNode{
public:
    ListNode(int v,ListNode *n) : next(n),val(v) {}
private:
    ListNode *next;
    int val;
};

int main()
{
    //n2->n1->NULL
    ListNode *n1 = new ListNode(1,NULL);
    ListNode *n2 = new ListNode(2,n1);
    return 0;
}
```

程序：

![](pic/12.png)

错误信息：

![](pic/12-1.png)

* **确定的内存泄露**
    - **直接的内存泄露**（**definitely lost**）：直接是没有任何指针指向该内存
    - **间接的内存泄露**（**indirectly lost**）：间接是指指向该内存的指针都位于内存泄露处，即由直接内存泄露引起的内存泄露
* **可能的内存泄露**（**possibly lost**）：指仍然存在某个指针能够访问某块内存，但该指针指向的已经不是该内存首地址

<br>

## 3.实现memcpy

> 实现的实际上是memmove，实际的memcpy是不考虑重叠的

重点在于**处理重叠**的情况：

```c
//#include<string.h>
void* memcpy(void *dst,const void *src,size_t size)
{
    if(dst == NULL || src == NULL){
        return NULL;
    }

    char *pdst = (char*)dst;
    char *psrc = (char*)src;

    //有重叠，从高地址开始复制
    if(pdst > psrc && pdst < psrc + size){
        pdst = pdst + size - 1;
        psrc = psrc + size - 1;
        while(size--){
            *pdst-- == *psrc--;
        }
    }
    //没有重叠，从低地址开始复制
    else{
        while(size--){
            *pdst++ = *psrc++;
        }
    }

    return dst;
}
```