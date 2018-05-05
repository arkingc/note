## 第一部分 基本套接字编程

<!-- GFM-TOC -->
* [一.套接字编程简介](#一套接字编程简介)
    * [1.端口号与套接字](#1端口号与套接字)
        * [1.1 端口号](#11-端口号)
        * [1.2 套接字](#12-套接字)
        * [1.3 TCP并发服务器中的套接字对](#13-tcp并发服务器中的套接字对)
    * [2.套接字地址结构](#2套接字地址结构)
        * [2.1 值-结果参数](#21-值-结果参数)
        * [2.2 字节操纵函数](#22-字节操纵函数)
        * [2.3 字节序](#23-字节序)
        * [2.4 地址转换](#24-地址转换)
* [二.基本TCP套接字编程](#二基本tcp套接字编程) 
    * [1.连接管理](#1连接管理)
    * [2.缓冲区](#2缓冲区)
    * [3.相关函数](#3相关函数)
* [三.基本UDP套接字编程](#三基本udp套接字编程)
    * [1.缓冲区](#1缓冲区)
    * [2.相关函数](#2相关函数)
* [四.I/O复用](#四io复用)
    * [1.select](#1select)
        * [1.1 描述符就绪条件](#11-描述符就绪条件) 
        * [1.2 select的优缺点](#12-select的优缺点)
    * [2.pselect](#2pselect)
    * [3.poll](#3poll)
        * [3.1 事件](#31-事件) 
        * [3.2 poll的优缺点](#32-poll的优缺点) 
    * [4.epoll](#4epoll) 
        * [4.1 工作模式](#41-工作模式) 
        * [4.2 epoll的优缺点](#42-epoll的优缺点)  
* [五.套接字选项](#五套接字选项)
    * [1.获取及设置套接字选项的函数](#1获取及设置套接字选项的函数)
    * [2.套接字选项分类](#2套接字选项分类)
        * [2.1 通用套接字选项](#21-通用套接字选项)
        * [2.2 TCP套接字选项](#22-tcp套接字选项)
* [六.名字与数值转换](#六名字与数值转换)
    * [1.主机名字与IP地址之间的转换](#1主机名字与ip地址之间的转换)
    * [2.服务名字与端口号之间的转换](#2服务名字与端口号之间的转换)
    * [3.主机与服务名字转IP地址与端口号](#3主机与服务名字转ip地址与端口号)
    * [4.IP地址与端口号转主机与服务名字](#4ip地址与端口号转主机与服务名字)
    * [5.其它网络相关信息](#5其它网络相关信息)
* [附1.回射服务器程序](#附1回射服务器程序)
    * [1.TCP回射服务器程序](#1tcp回射服务器程序)
    * [2.UDP回射服务器程序](#2udp回射服务器程序) 
* [附2.头文件映射表](#附2头文件映射表)
    * [1.类型与头文件映射表](#1类型与头文件映射表)
    * [2.函数与头文件映射表](#2函数与头文件映射表)
<!-- GFM-TOC -->

## 第二部分 高级套接字编程



<br>
<br>
<br>

# 一.套接字编程简介

## 1.端口号与套接字

### 1.1 端口号

IANA(因特网已分配数值权威机构)维护着一个端口号分配状况的清单。该清单一度作为RFC多次发布；端口号被划分成3段：

* **众所周知的端口(0\~1023)**：这些端口由IANA分配和控制。可能的话，相同端口号就分配给TCP、UDP和SCTP的同一给定服务。（如，不论TCP还是UDP端口号80都被赋予Web服务器，尽管它目前的所有实现都单纯的使用TCP）
* **已登记的端口(1024\~49151)**：这些端口不受IANA控制，不过由IANA登记并提供它们的使用情况清单，以方便整个群体。可能的话，相同端口号也分配给TCP和UDP的同一给定服务。49151这个上限的引入是为了给临时端口留出范围
* **动态、私用的端口(49152\~65535)**：IANA不管这些端口。就是我们所称的临时端口

<div align="center"> <img src="../pic/unp-2-1.png"/> </div>

### 1.2 套接字

一个**TCP套接字对**是一个定义该连接的两个端点的四元组

```
{本地IP,本地TCP端口号,外地IP,外地TCP端口号}
```

**套接字对唯一标识一个网络上的每个TCP连接**

标识每个端点的两个值（IP地址和端口号）通常称为一个套接字

### 1.3 TCP并发服务器中的套接字对

1. **服务器端在21号端口监听，等待来自客户端的连接**

<div align="center"> <img src="../pic/unp-2-2.png"/> </div>

使用记号{\*:21,\*:\*}指出服务器的套接字对

* 第一个星号：服务器在任意本地接口的端口21上等待连接请求
* 第二个和第三个星号：等到任意IP，任意端口的连接

2. **主机206.168.112.219上的第一个客户发起一个连接，临时端口1500**：

<div align="center"> <img src="../pic/unp-2-3.png"/> </div>

3. **连接建立后，服务器fork一个子进程处理该客户的请求**：

<div align="center"> <img src="../pic/unp-2-4.png"/> </div>

4. **主机206.168.112.219上一个新的客户发起一个连接，服务器fork另一个子进程处理新客户的请求（由于临时端口不同，所有和前一个连接不是相同的连接）**：

<div align="center"> <img src="../pic/unp-2-5.png"/> </div>

## 2.套接字地址结构

大多数套接字函数都需要一个指向套接字地址结构的指针作为参数。每个协议族都定义了自己的套接字地址结构

**套接字地址结构仅在给定主机上使用：虽然结构中的某些字段用在不同主机之间的通信中，但是结构本身并不在主机之间传递**

<div align="center"> <img src="../pic/unp-3-1.png"/> </div>

* **sockaddr_in**
    * IPv4地址和TCP或UDP端口号在套接字地址结构中总是以**网络字节序**来存储
    * POSIX规范只需要这个结构中的下列3个字段
        - sin_family：可以是任何无符号整数类型。在支持长度字段的实现中，通常是8位无符号整数，在不支持长度字段的实现中，则是16位无符号整数
        - sin_addr：in_addr_t必须至少是32位的无符号整数类型
        - sin_port：in_port_t必须至少是16位的无符号整数类型
    * sin_zero字段未曾使用
    * **长度是16**
* **sockaddr_in6**
    * 如果系统支持长度字段，那么SIN6_LEN常值必须定义
    * **长度是28**
* **sockaddr_storage**相比于**sockaddr**的优势：
    - 如果系统支持的任何套接字地址结构有对齐的需要，那么sockaddr_storage能够满足最苛刻的对齐要求
    - sockaddr_storage足够大，能够容纳系统支持的任何套接字地址结构
* **sockaddr_storage**结构中除了上图中的两个字段，其它字段都是透明的，必须强制转换成其它类型套接字地址结构才能访问其它字段

[套接字地址结构所在头文件](https://github.com/arkingc/note/blob/master/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/%E6%8E%A5%E5%8F%A3%E4%B8%8E%E5%A4%B4%E6%96%87%E4%BB%B6.md#%E7%B1%BB%E5%9E%8B)

### 2.1 值-结果参数

**1）从进程到内核传递套接字地址结构**：bind、connect、sendto

<div align="center"> <img src="../pic/unp-3-2.png"/> </div>

**2）从内核到进程传递套接字地址结构**：accept、recvfrom、getsockname、getpeername
* **值**：告诉内核该结构的大小，内核在写结构时不至于越界
* **结果**：告诉进程内核在该结构中实际存储了多少信息（如果套接字地址结构是**固定长度**的，那么从内核返回的值总是那个固定长度，如IPv4的sockaddr_in长度是16，IPv6的sockaddr_in6长度是28；对于**可变长度**的套接字地址结构，返回值可能小于结构的最大长度）

<div align="center"> <img src="../pic/unp-3-3.png"/> </div>

> 这里只是使用“套接字地址结构的长度”作为例子，来解释“值-结果”参数，还有其它的”值-结果“参数

### 2.2 字节操纵函数

操纵多字节字段的函数有2组：

```c
/***********************************************************************
 *  第一组：起源于4.2BSD，几乎所有现今支持套接字函数的系统仍然提供
 **********************************************************************/
#include <strings.h>
void bzero(void *dest,size_t nbytes);
void bcopy(const void *src,void *dest,size_t nbytes);
int bcmp(const void *ptr1,const void *ptr2,size_t nbytes);

/***********************************************************************
 *  第二组：起源于ANSI C，支持ANSI C函数库的所有系统都提供
 **********************************************************************/
#include <string.h>
void* memset(void *dest,int c,size_t len);
void* memcpy(void *dest,const void *src,size_t nbytes);
int memcmp(const void *ptr1,const void *ptr2,size_t nbytes);
```

* bzero相比于memset只有2个参数
* bcopy能够正确处理源“字节串”与目标“字节串”重叠，memcpy不行（可以用memmove）

>bzero和memset可用于**套接字地址结构**的初始化

### 2.3 字节序

* **小端字节序**：低序字节存储在起始地址
* **大端字节序**：高序字节存储在起始地址

<div align="center"> <img src="../pic/unp-3-4.png"/> </div>

* **主机字节序**：某个给定系统所用的字节序
* **网络字节序**：网络协议必须指定一个网络字节序。举例来说，在每个TCP分节中都有16位的端口号和32位的IPv4地址。发送协议栈和接收协议栈必须就这些多字节字段各个字节的传送顺序达成一致（**网际协议使用大端字节序**传送这些多字节整数）

从理论上说，具体实现可以按主机字节序存储套接字地址结构中的各个字段，等到需要在这些字段和协议首部相应字段之间移动时，再在主机字节序和网络字节序之间进行转换，让我们免于操心转换细节。然而由于历史原因和POSIX规范的规定，**套接字地址结构中的某些字段必须按照网络字节序进行维护**

#### 主机字节序与网络字节序的转换函数

```c
#include <netinet/in.h>

/***********************************************
 * 主机字节序 -> 网络字节序
 ***********************************************/
uint16_t htons(uint16_t host16bitvalue);
uint32_t htonl(uint32_t host32bitvalue);

/***********************************************
 * 网络字节序 -> 主机字节序
 ***********************************************/
uint16_t ntohs(uint16_t net16bitvalue);
uint32_t ntohl(uint32_t net32bitvalue);
```

### 2.4 地址转换

有两组函数可以完成**ASCII字符串与网络字节序的二进制值之间的转换**：

```c
#include<arpa/inet.h>

/********************************************************************
 * 第一组：只支持IPv4；
 *        strptr：指向C字符串，表示点分十进制的地址
 *        addrptr/inaddr：网络字节序二进制值
 *        inet_addr函数：如今已废弃，新代码应该使用inet_aton（该函数出错时，
 *                      返回INADDR_NONE，32位均为1，因此255.255.255.255
 *                      不能由该函数处理）
 *        inet_ntoa函数：参数传入的是结构而不是结构的指针；
 *                      返回值所指字符串在静态区，故函数不可重入
 ********************************************************************/
int inet_aton(const char *strptr,struct in_addr *addrptr);//字符串有效返回1，否则0
int_addr_t inet_addr(const char *strptr);
char* inet_ntoa(struct in_addr inaddr);

 /**************************************************************
 * 第二组：既支持IPv4也支持IPv6；
 *        两个函数的family参数既可以是AF_INET，也可以是AF_INET6。如果
 *        以不被支持的地址族作为family参数，将返回一个错误，并将errno置
 *        为EAFNOSUPPORT；
 *        strptr：指向C字符串，表达式格式
 *        addrptr：网络字节序二进制值，数值格式
 *        len：strptr指向的内存区的大小，防止溢出
 ***************************************************************/
int inet_pton(int family,const char *strptr,void *addrptr);//成功返回1，字符串无效返回0，出错-1
const char* inet_ntop(int family,const void *addrptr,char *strptr,size_t len);
```

<br>

# 二.基本TCP套接字编程

<div align="center"> <img src="../pic/unp-tcp-1.png"/> </div>

TCP提供了可靠传输，当TCP向另一端发送数据时，要求对端返回一个确认。如果没有收到确认，TCP就重传数据并等待更长时间。在数次重传失败后，TCP才放弃，如此在尝试发送数据上所花的总时间一般为4~10分钟（依赖于具体实现）

在上图中，服务器对客户端请求的确认伴随其应答一起发送给客户端，即**捎带**（通常在服务器处理请求并产生应答的时间少于200ms时发生。如果服务器耗用更长时间，譬如说1s，那么会先确认然后应答）

> 如果类似上图这样，连接的整个目的仅仅是发送一个单分节的请求和接收一个单分节的应答，那么使用TCP有8个分节的开销。如果改用UDP，那么只需交换两个分组：一个承载请求，一个承载应答。然后从TCP切换到UDP将丧失TCP提供给应用进程的全部可靠性，迫使可靠服务的一大堆细节从(TCP)传输层转移到(UDP)应用进程。TCP提供的拥塞控制也必须由UDP应用进程来处理

## 1.连接管理

连接建立的前2次握手中，每一个SYN可以包含多个TCP选项：

* **MSS选项**：向对端通告**最大分节大小**，即MSS，也就是愿意接收的最大数据量。发送端TCP使用接收端的MSS值作为所发送分节的最大大小（可以通过TCP_MAXSEG套接字选项提取和设置）
* **窗口规模选项**：TCP首部中接收窗口首部为16位，意味着能通告对端的最大窗口大小是65535。然而这个值现今已不够用，窗口规模选项用于指定TCP首部中接收窗口必须扩大(即左移)的位数(0~14)，因此所提供的最大窗口接近1GB(65535x2^14)（**使用前提是两个端系统都支持该选项**）

## 2.缓冲区

每一个TCP套接字有一个发送缓冲区，可以使用SO_SNDBUF套接字选项更改该缓冲区的大小。当某个进程调用write时，内核从该应用进程的缓冲区中复制所有数据到所写套接字的发送缓冲区

<div align="center"> <img src="../pic/unp-tcp-2.png"/> </div>

如果该套接字的发送缓冲区容不下该应用进程的所有数据（或是应用进程的缓冲区大于套接字的发送缓冲区，或者套接字的发送缓冲区中已有其他数据），该应用进程将被投入睡眠（这里假设是默认情况下，默认情况下套接字是阻塞的）。内核将不从write系统调用返回，直到应用进程缓冲区中的所有数据都复制到套接字发送缓冲区。因此，**从写一个TCP套接字的write调用成功返回仅仅表示我们可以重新使用原来的应用进程缓冲区，并不表明对端的TCP或应用进程已接收到数据**

TCP套接字提取发送缓冲区中的数据并把它发给对端TCP，对端TCP必须确认收到的数据，**伴随来自对端的ACK的不断到达，本端TCP至此才能从套接字发送缓冲区中丢弃已确认的数据。TCP必须为已发送的数据保留一个副本，直到它被对端确认为止**

MSS的目的之一就是试图避免分片，较新的实现还使用了路径MTU发现功能。每个数据链路都有一个输出队列，如果队列已满，那么新到的分组将被丢弃，并沿协议栈向上返回一个错误：从数据链路到IP，再从IP到TCP。TCP将注意到这个错误，并在以后某个时刻重传相应的分节。应用进程并不知道这种暂时的情况

## 3.相关函数

### 1）socket函数

<div align="center"> <img src="../pic/unp-tcp-3.png"/> </div>

* **family**：指定协议族，也往往被称为协议域

<div align="center"> <img src="../pic/unp-tcp-4.png"/> </div>

* **type**：指明套接字的类型

<div align="center"> <img src="../pic/unp-tcp-6.png"/> </div>

* **protocol**：协议类型常值。设为0的话表示选择所给定family和type组合的系统默认值

<div align="center"> <img src="../pic/unp-tcp-5.png"/> </div>

family和type的有效组合如下：

<div align="center"> <img src="../pic/unp-tcp-7.png"/> </div>

### 2）connect函数

<div align="center"> <img src="../pic/unp-tcp-8.png"/> </div>

* **sockfd**：客户端套接字描述符
* **servaddr**：包含服务器IP地址和端口号的套接字地址结构
* **addrlen**：套接字地址结构的大小

调用connect前不必非得调用bind，如果每调用，内核会确定源IP并选择一个临时端口作为源端口

如果是TCP套接字，调用connect将激发TCP三路握手过程，函数会阻塞进程，直到成功或出错才返回。出错可能有下列情况：

1. **返回ETIMEDOUT错误**：以4.4BSD为例，内核会先发送一个SYN，若无响应则等待6s后再发送一个，若仍无响应则等待24s后再发送一个。若总共等待了75s后仍未收到响应则返回该错误
2. **返回ECONNREFUSED错误**：服务器对客户响应一个RST，表明服务器在客户指定的端口上没有进程在等待与之连接（除此之外，产生RST还有两个条件：1）TCP想取消一个已有连接；2）TCP接收到一个根本不存在的连接上的分节）
3. **返回EHOSTUNREACH或ENETUNREACH错误**：客户发出的SYN在中间的某个路由引发一个“目的地
不可达”ICMP错误，内核会报错该消息，并情况1中的的间隔继续发送SYN，若在规定时间内仍未收到响应，则把报错的信息作为这两种错误之一返回给进程

**connect失败则该套接字不可再用，必须关闭，不能对这样的套接字再次调用connect函数。必须close后重新调用socket**

### 3）bind函数

bind把一个本地协议地址赋予一个套接字

<div align="center"> <img src="../pic/unp-tcp-9.png"/> </div>

调用bind可以指定IP地址或端口，可以两者都指定，也可以都不指定：

<div align="center"> <img src="../pic/unp-tcp-10.png"/> </div>

* 如果指定端口号为0，内核在bind被调用时选择一个临时端口
* 如果指定IP地址为通配地址（对IPv4来说，通配地址由常值INADDR_ANY来指定，值一般为0），内核将等到套接字已连接(TCP)或已在套接字上发出数据报(UDP)时才选择一个本地IP地址

**如果让内核来为套接字选择一个临时端口号，函数bind并不返回所选择的值。第二个参数有const限定词，它无法返回所选的值。如果想得到内核所选择的临时端口值，必须调用getsockname函数**

bind返回的一个常见错误是EADDRINUSE("Address already in use")

### 4）listen函数

listen做2件事：

* 当socket创建一个套接字时，套接字被假设为一个主动套接字，listen将其转成一个被动套接字，指示内核应接受指向该套接字的连接请求
* **第二个参数规定了内核应为相应套接字排队的最大连接个数**

<div align="center"> <img src="../pic/unp-tcp-11.png"/> </div>

内核为任一给定的监听套接字维护两个队列，两个队列之和不超过backlog：

* **未完成连接队列**
* **已完成连接队列**

<div align="center"> <img src="../pic/unp-tcp-12.png"/> </div>

当进程调用accept时，如果已连接队列不为空，那么队头项将返回给进程，否则进程将投入睡眠，直到TCP在该队列中放入一项才唤醒它

不要把backlog指定为0，因为不同的实现对此有不同的解释。如果不想让任何客户连接到监听套接字上，那就关掉该监听套接字

设置backlog的一种方法是使用一个常值，但是增大其大小需要重新编译服务器程序；另一种方法是通过读取一个环境变量来设置该值，该环境变量具有一个默认值；（如果设定的backlog比内核支持的值要大，那么内核会悄然把所指定的偏大值截成自身支持的最大值）

**SYN到底是，如果队列已满，TCP忽略该SYN分节**：这么做是因为这种情况是暂时的，这种处理方式希望通过重传机制，在客户端下一次重传时，队列中已经存在可用空间。如果服务器立即响应RST，客户的connect调用就会立即返回一个错误，抢占应用程序处理这种情况。另外，客户也无法区分RST是意味着“该端口没有服务器在监听”还是意味着“队列已满”

### 5）accept函数

accept用于从已完成连接队列队头返回下一个已完成连接，如果已完成连接队列为空，那么进程被投入睡眠

<div align="center"> <img src="../pic/unp-tcp-13.png"/> </div>

* **sockfd**：监听套接字描述符
* **cliaddr**：已连接的对端客户的套接字地址结构
* **addrlen**：调用时指示内核能向cliaddr写入的最大字节数，返回时内核指明实际写入的字节数

如果对返回客户协议地址不感兴趣，可以把cliaddr和addrlen均置为空指针

### 6）close函数

<div align="center"> <img src="../pic/unp-tcp-14.png"/> </div>

close一个TCP套接字的默认行为是把套接字标记为关闭，立即返回调用进程，然后TCP将尝试发送已排队等待发送到对端的任何数据，发送完毕后是正常的TCP连接终止序列

close会将套接字描述符的引用计数减1，如果引用计数仍大于0，则不会引起TCP的四次挥手终止序列

### 7）getsockname和getpeername函数

这两个函数与TCP连接建立过程中套接字地址结构的信息获取相关

<div align="center"> <img src="../pic/unp-tcp-16.png"/> </div>

* **getsockname用于返回与某个套接字关联的本地协议地址**：
    - 没调用bind的TCP客户上，connect返回后，获取由内核赋予该连接的本地IP地址和端口号
    - 以端口号0调用bind后，获取由内核赋予的本地端口号
    - 获取某个套接字的地址族
    - 绑定通配IP的服务器上，accept返回后，获取由内核赋予该连接的本地IP地址，此时sockfd不是监听套接字描述符
* **getpeername用于返回与某个套接字关联的外地协议地址**：
    - 当一个服务器是由调用过accept的某个进程通过调用exec执行程序时，它能获取客户身份的唯一途径便是调用getpeername。例如inetd fork并exec某个TCP服务器程序：

<div align="center"> <img src="../pic/unp-tcp-15.png"/> </div>

<br>

# 三.基本UDP套接字编程

典型的UDP客户/服务器程序的函数调用：

<div align="center"> <img src="../pic/unp-8-1.png"/> </div>

## 1.缓冲区

发送缓冲区用虚线表示，因为实际上并不存在。任何UDP套接字都有发送缓冲区大小（同样可以使用SO_SNDBUF套接字选项更改），不过该缓冲区仅表示能写到该套接字的UDP数据报的大小上限。如果应用进程写一个大于套接字发送缓冲区大小的数据报，内核将返回该进程一个EMSGSIZE错误。

<div align="center"> <img src="../pic/unp-udp-1.png"/> </div>

因为UDP是不可靠的，不必保存应用进程数据的一个副本，所以不需一个真正的发送缓冲区。（应用进程的数据在沿协议栈向下传递时，通常被复制到某种格式的一个内核缓冲区中，然而当该数据被发送之后，这个副本就被数据链路层丢弃了）

如果某个UDP应用进程发送大数据报，那么它们相比TCP应用数据更有可能被分片，因为TCP会把应用数据划分成MSS大小的块，而UDP却没有对等的手段

从写一个UDP套接字的write调用成功返回，表示所写的数据报或其所有片段已被加入数据链路层的输出队列。如果该队列没有足够的空间存放该数据报或它的某个片段，内核通常会返回一个ENOBUFS错误给它的应用进程（不幸的是，有些UDP的实现不返回这种错误，这样甚至数据报未经发送就被丢弃的情况应用进程也不知道）

## 2.相关函数

### 1）recvfrom与sendto函数

<div align="center"> <img src="../pic/unp-8-2.png"/> </div>

* **recvfrom**：
    - **from**：指向一个将由该函数在返回时填写数据报发送者的协议地址的套接字地址结构
    - **addrlen(指针)**：在from指向的套接字地址结构中填写的字节数
* **sendto**：
    - **to**：指向一个含有数据报接收者的协议地址的套接字地址结构
    - **addrlen(整数)**：指定to指向的套接字地址结构的大小

**recvfrom的from参数可以是一个空指针，此时addrlen也必须是一个空指针，表示并不关心数据发送者的协议地址**

**写一个长度为0的数据报是可行的。在UDP情况下，这会形成一个只包含一个IP首部（对于IPv4通常为20字节，对于IPv6通常为40字节）和一个8字节UDP首部而没有数据的IP数据报。这也意味着对于数据报协议，recvfrom返回0值是可接受的：它并不像TCP套接字上read返回0值那样表示对端已关闭连接。既然UDP是无连接的，因此也就没有诸如关闭一个UDP连接之类的事情**

**接收缓冲**：UDP层中隐含有排队发生。事实上每个UDP套接字都有一个接收缓冲区，到达该套接字的每个数据报都进入这个套接字接收缓冲区。当进程调用recvfrom时，缓冲区中的下一个数据报以FIFO顺序返回给进程、这样，在进程能够读该套接字中任何已排好队的数据报之前，如果有多个数据报到达该套接字，那么相继到达的数据报仅仅加到该套接字的接收缓冲区中。这个缓冲区的大小是有限的

**对于一个UDP套接字，如果其进程首次调用sndto时，它没有绑定一个本地端口，那么内核就在此时为它选择一个临时端口**

<div align="center"> <img src="../pic/unp-8-3.png"/> </div>

圆点指明了客户发送UDP数据报时，必须指定或选择的4个值

* 客户必须给sendto调用指定**服务器的IP地址和端口号**
* **客户的IP地址和端口号**可以(调用bind)指定也可以不指定
    - **如果客户没有捆绑具体的IP和端口号，内核会自动选择**：
        + 临时**端口**是在第一次调用sendto时一次性选定，不能改变
        + **IP地址**却可以随客户发送的每个UDP数据报而变动
    - **如果客户绑定了一个IP地址**：
        + 在这种情况下，如果内核决定外出数据报必须从另一个数据链路发出，IP数据报将会包含一个不同于外出链路IP地址的源IP地址

在一个未绑定(指定)端口号和IP地址的UDP套接字上调用connect时，会给该套接字指派一个IP地址和临时端口

TCP和UDP服务器上获取**源IP**、**源端口号**、**目的IP**、**目的端口号**的方法：

<div align="center"> <img src="../pic/unp-8-4.png"/> </div>

* 非连接状态下，同一套接字可以给多个服务器发送数据报
* 服务器上同一套接字可以从若干不同客户段接收数据报

> recvfrom和sendto都可以用于TCP，尽管通常没有理由这样做

### 2）connect函数

<div align="center"> <img src="../pic/unp-tcp-8.png"/> </div>

* **sockfd**：客户端套接字描述符
* **servaddr**：包含服务器IP地址和端口号的套接字地址结构
* **addrlen**：套接字地址结构的大小

给UDP套接字调用connect并不会像TCP一样触发三路握手，内核只是**检查是否存在立即可知的错误，记录对端的IP地址和端口号，然后立即返回**

已连接的UDP套接字与默认的未连接UDP套接字有3个不同：

1. **不能再给输出操作指定目的IP地址和端口号，即不使用sendto而改用write或send**
2. **不必使用recvfrom以获悉数据报的发送者，而改用read、recv或recvmsg**（发源地不是该套接字早先connect到的协议地址的数据报不会投递到该套接字，从而限制了一个已连接套接字能且仅能与一个对端交换数据）
3. **由已连接UDP套接字引发的异步错误会返回给她们所在的进程。未连接时不接收任何异步错误**

一个拥有**已连接UDP套接字**的进程，可出于下列2个目的再次调用connect：

* **指定新的IP地址和端口号**
* **断开套接字**：调用connect时，把套接字地址结构的地址族成员设置为AF_UNSPEC

TCP要再次调用connect必须先close套接字再重新调用socket创建套接字描述符

**当应用进程在一个未连接的UDP套接字上调用sendto时，源自Berkeley的内核暂时连接该套接字，发送数据报，然后断开该连接**。因此，当应用进程要给同一目的地址发送多个数据报时，使用连接套接字可以获得更高的效率

<br>

# 四.I/O复用

**I/O复用是一种机制，一个进程可以监视多个描述符，一旦某个描述符就绪（一般是读就绪或写就绪），能够通知程序进行相应的读写操作。**

目前支持I/O复用的系统调用有```select、pselect、poll、epoll```，本质上这些I/O复用技术都是同步I/O，在读写事件就绪后需要进程自己负责进行读写，即读写过程是进程阻塞的

**与多进程和多线程相比，I/O复用技术的最大优势是系统开销小，系统不必创建进程/线程，也不必维护这些进程/线程，从而大大减小了系统的开销**

## 1.select

```c
/********************************************************************
 * 参数：
 *     maxfdp1：指定待测试的描述符个数，值为待测试的最大描述符加1（参数名的由来）
 *     readset：读描述符集
 *     writeset：写描述符集
 *     exceptset：异常描述符集。目前支持的异常条件只有两个
 *         1）某个套接字的带外数据到达
 *         2）某个已设置为分组模式的伪终端存在可从其主端读取的控制状态信息
 *     timeout：(告知)内核等待任意描述符就绪的超时时间，超时函数返回0
 *         1）永远等待下去：设为空指针
 *         2）等待一段固定时间
 *         3）立即返回(轮询)：timeval结构中的时间设为0
 * 描述符集说明：
 *     1）select使用的描述符集，通常是一个整数数组，其中每个整数中的一位对应一个描述符
 *     2）如果对三个描述符集中的某个不感兴趣，可以设为空指针，如果都设为空指针，会得到
 *        一个比Unix的sleep函数更精确的定时器（sleep以秒为最小单位）
 *     3）<sys/select.h>中定义的FD_SETSIZE常值是数据类型fd_set中的描述符总数，其
 *        值通常是1024，不过很少用到这么多描述符，maxfdp1参数迫使我们计算
 * 返回值：
 *     正数：跨所有描述符集的已就绪描述符的“数目”
 *     0：超时
 *     -1：出错
 ********************************************************************/
#include <sys/select.h>
#include <sys/time.h>
int select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set exceptset,const struct timeval *timeout);

/********************************************************************
 * 设置描述符集
 * 
 * 描述符集是“值-结果“参数，select调用返回时，结果将指示哪些描述符已就绪。函数返回后，使用FD_ISSET宏来测试fd_set数据类型中的描述符。描述符集内任何与未就绪福描述符
 * 对应的位返回时均清为0。因此，每次重新调用select函数时，都得再次把所有描述符集
 * 内所关心的位设置为1
 ********************************************************************/
void FD_ZERO(fd_set *fdset);            //清除fdset的所有位
void FD_SET(int fd,fd_set *fdset);      //打开fdset中的fd位
void FD_CLR(int fd,fd_set *fdset);      //清除fdset中的fd位
int FD_ISSET(int fd,fd_set *fdset);     //检查fdset中的fd位是否置位
```

### 1.1 描述符就绪条件

* **套接字可读**：
    - 套接字接收缓冲区中的数据(字节数)大于等于套接字接收缓冲区**低水位标记**的当前大小
    - 连接的读半部关闭（也就是接收了FIN的TCP连接），对这样的套接字读不会阻塞并返回0(EOF)
    - 监听套接字已完成的连接数不为0。对其accept通常不阻塞
    - 套接字上有一个错误，对其读不会阻塞并返回-1，同时把errno设为确切错误条件
* **套接字可写**：
    - 套接字发送缓冲区中的可用空间(字节数)大于等于套接字发送缓冲区**低水位标记**的当前大小，并且或者该套接字已连接，或者该套接字不需要连接(如UDP套接字)
    - 连接的写半部关闭，对这样的套接字写将产生SIGPIPE信号
    - 使用非阻塞式connect的套接字已建立连接，或者connect以失败告终
    - 套接字上有一个错误，对其写将不会阻塞并返回-1，同时把errno设为确切错误条件
* **套接字有异常条件待处理**

<div align="center"> <img src="../pic/unp-6-1.png"/> </div>

> 设置低水位标记
> * 可以使用SO_RCVLOWAT套接字选项设置套接字接收缓冲区低水位标记（对于TCP和UDP，默认值为1）
> * 可以使用SO_SNDLOWAT套接字选项设置套接字发送缓冲区低水位标记（对于TCP和UDP，默认值为2048）

### 1.2 select的优缺点

* **优点**：
    - **跨平台支持好**，目前几乎在所有平台上支持
* **缺点**：
    - **最大的缺点是，进程打开的fd有限**（由FD_SETSIZE和内核决定，一般为1024），这对于连接数量比较大的服务器来说根本不能满足（可以选择多进程的解决方案，虽然Linux上创建进程的代价比较小，但也不可忽视，加上进程间数据同步远比不上线程间同步的效率，所以也不是一直完美的方案）
    - **函数返回后需要轮询描述符集，寻找就绪描述符，效率不高**
    - **用户态和内核态传递描述符结构时copy开销大**

## 2.pselect

```c
/********************************************************************
 * 参数：
 *     maxfd1：指定待测试的描述符个数，值为待测试的最大描述符加1（参数名的由来）
 *     readset：读描述符集
 *     writeset：写描述符集
 *     exceptset：异常描述符集。目前支持的异常条件只有两个
 *         1）某个套接字的带外数据到达
 *         2）某个已设置为分组模式的伪终端存在可从其主端读取的控制状态信息
 *     timeout：(告知)内核等待任意描述符就绪的超时时间，超时函数返回0
 *         1）永远等待下去：设为空指针
 *         2）等待一段固定时间
 *         3）立即返回(轮询)：timeval结构中的时间设为0
 *     sigmask：
 * 返回值：
 *     正数：跨所有描述符集的已就绪描述符的“数目”
 *     0：超时
 *     -1：出错
 ********************************************************************/
#include <sys/select.h>
#include <signal.h>
#include <time.h>
int pselect(int maxfd1,fd_set *readset,fd_set *writeset,fd_set *exceptset,
    const struct timespec *timeout,const sigset_t *sigmask);
```

pselect相对于通常的select有2个变化：

1. **使用timespec结构，而不是timeval结构**。timespec的第二个成员是纳秒级，2而timeval的第二个成员是微妙级
2. **增加了第6个参数：一个指向信号掩码的指针**。该参数运行程序先禁止递交某些信号，再测试由这些当前被禁止信号的信号处理函数设置的全局变量，然后调用pselect，告诉它重新设置信号掩码

## 3.poll

```c
/********************************************************************
 * 参数：
 *     fds：
 *     nfds：读描述符集合
 *     timeout：(告知)内核等待任意描述符就绪的超时时间，超时函数返回0
 *         1）永远等待下去：INFTIM（一个负值）
 *         2）等待一段固定时间：>0
 *         3）立即返回(轮询)：0
 * 返回值：
 *     正数：所有已就绪描述符的“数目”
 *     0：超时
 *     -1：出错
 ********************************************************************/
#include <poll.h>
int poll(struct pollfd *fds,unsigned int nfds,int timeout);

/********************************************************************
 * 如果不再关心某个特定描述符，可以把与之对应的pollfd结构的fd成员设置成一个负值
 * poll函数将忽略这样的pollfd结构的events成员，返回时将其revents成员的值置为0
 ********************************************************************/
struct pollfd{
    int fd;         //监视的描述符
    short events;   //该描述符上监视的事件
    short revents;  //该描述符上发生的事件
};
```

### 3.1 事件

poll中每个描述符有一个监视的事件以及一个发生的事件，在pollfd结构中是类型为short的成员。两个成员中的每一个都由指定某个特定条件的一位或多位构成：

<div align="center"> <img src="../pic/unp-6-2.png"/> </div>

* **第一部分是处理输入的4个常值**
* **第二部分是处理输出的3个常值**
* **第三部分是处理错误的3个常值**

对于TCP和UDP而言，以下条件将引起poll返回特定的revent：

* 所有正规TCP数据和所有UDP数据都被认为是**普通数据**
* TCP的带外数据被认为是**优先级带数据**
* TCP连接读半部关闭时（如收到一个来自对端的FIN），被认为是**普通数据**，随后读操作返回0
* TCP连接存在错误既可认为是**普通数据**，也可认为是**错误**。随后的读操作返回-1，并设置error（可用于处理诸如接收到RST或发生超时等条件）
* 在监听套接字上有新连接可用，既可认为是**普通数据**也可认为是**优先级带数据**

### 3.2 poll的优缺点

* **优点**：
    - **没有最大监视描述符数量的限制**：分配一个pollfd结构的数组并把该数组中元素的数目通知内核成了调用者的责任。内核不再需要知道类似fd_set的固定大小的数据类型
* **缺点**：
    - 和select一样，调用返回后需要**轮询所有描述符来获取已经就绪的描述符**
    - **用户态和内核态传递描述符结构时copy开销大**

## 4.epoll

```c
/********************************************************************
 * 创建一个epoll句柄
 * 参数：
 *     size：告诉内核监听的数量，并不是监听数量的最大值，是对内核初始分配内部数
 *           据结构的一个建议
 * 返回值：
 *     创建的epoll句柄
 ********************************************************************/
int epoll_create(int size);

/********************************************************************
 * 对指定描述符fd执行op操作
 * 参数：
 *     epfd：epoll_create得到的epoll句柄
 *     op：操作
 *         1）EPOLL_CTL_ADD：添加
 *         2）EPOLL_CTL_DEL：删除
 *         3）EPOLL_CTL_MOD：修改
 *     fd：需要监听的fd
 *     event：告知内核需要监听的事件
 *         1）EPOLLIN：对应的描述符可读
 *         2）EPOLLOUT：对应的描述符可写
 *         3）EPOLLPRI：对应的描述符有紧急数据可读（带外数据）
 *         4）EPOLLERR：对应的描述符发生错误
 *         5）EPOLLHUP：对应的描述符被挂断
 *         6）EPOLLET：将epoll设为边缘触发模式
 *         7）EPOLLONESHOT：只监听一次事件，监听完后，如果需要再次监听这个socket，
 *                          需要再次把这个socket加入到epoll队列
 * 返回值：
 *     
 ********************************************************************/
int epoll_ctl(int epfd,int op,int fd,struct epoll_event *event);

struct epoll_event{
    __uint32_t events;
    epoll_data_t data;
};

/********************************************************************
 * 等待epoll句柄上的I/O事件，最多返回maxevents个事件
 * 参数：
 *     epfd：epoll_create得到的epoll句柄
 *     events：从内核得到事件的集合
 *     maxevents：返回事件的最大数量（不能大于创建epoll句柄时的size参数）
 *     timeout：超时参数
 *         1）立即返回：0
 *         2）永久阻塞？：-1
 * 返回值：
 *     >0：返回需要处理的事件数目
 *     0：超时
 ********************************************************************/
int epoll_wait(int epfd,struct epoll_event *events,int maxevents,int timeout);
```

### 4.1 工作模式

**epoll对描述符的操作有两种模式，当epoll_wait检测到描述符事件发生时，向应用程序通常此事件**：

* **水平触发(LT)模式(默认)**：
    - 应用程序可以不立即处理该事件。下次调用epoll_wait时，会再次向应用程序通知此事件
    - 支持阻塞或非阻塞套接口
* **边缘触发(ET)模式**：
    - 应用程序必须立即处理该事件。如果不处理，下次调用epoll_wait时，不再向应用程序通知此事件
    - 只支持非阻塞套接口（以免一个文件句柄的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死）

**ET模式在很大程度上减少了epoll事件被重复触发的次数，因此效率要比LT模式高**

### 4.2 epoll的优缺点：

* **优点**
    * **监视的描述符数量不受限制**，所支持的FD上限是最大可以打开文件的数目
    * **I/O效率不会随着监视fd数量的增长而下降**：epoll不同于select和poll轮询的方式，而是通过每个fd定义的回调函数来实现的，只有就绪的fd才会执行回调函数
    * **用户态和内核态消息传递的开销小**：利用mmap()减少复制开销

> 如果没有大量的“idle连接”或“dead连接”，epoll的效率并不会比select/poll高很多
> * 当连接数少并且连接都十分活跃的情况下，select和poll的性能可能比epoll好
> * 当遇到大量的"idle连接"，epoll的效率会大大高于select/poll

<br>

# 五.套接字选项

<div align="center"> <img src="../pic/unp-7-7.png"/> </div>

## 1.获取及设置套接字选项的函数

* **getsockopt和setsockopt函数**
* **fcntl函数**
* **ioctl函数**

#### 1）getsockopt和setsockopt函数

<div align="center"> <img src="../pic/unp-7-1.png"/> </div>

* **sockfd**：一个打开的套接字描述符
* **level**：系统中解释选项的代码。或为通用套接字代码，或为某个特定于协议的代码（IPv4、IPv6、TCP或SCTP）
* **optname**：选项名
* **optval**：setsockopt从optval中取得选项待设置的新值，getsockopt则把已获取的选项当前值存放到optval中（给标志选项调用getsockopt函数时，\*optval是一个整数。\*optval中返回的值为0表示相应选项被禁止，不为0表示相应选项被启用；给标志选项调用setsockopt函数需要一个不为0的\*optval值来启用选项，一个为0的\*optval值来禁止选项）
* **optlen**：指明optval所指结构的大小

#### 2）fcntl函数

<div align="center"> <img src="../pic/unp-7-6.png"/> </div>

* **fd**：套接字描述符
* **cmd**：作用于该描述符上的命令
    - **F_GETFL**：获取文件标志（影响套接字描述符的两个标志：O_NONBLOCK(非阻塞式I/O)、O_ASYNC(信号驱动式I/O)）
    - **F_SETFL**：设置文件标志（影响套接字描述符的两个标志：O_NONBLOCK(非阻塞式I/O)、O_ASYNC(信号驱动式I/O)）
    - **F_SETOWN**：指定用于接收SIGIO和SIGURG信号的套接字属主（进程ID或进程组ID），SIGIO信号是套接字被设置为信号驱动式I/O后产生的，SIGURG信号是在新的带外数据到达套接字时产生的
        + SIGIO和SIGURG与其他信号的不同之处在于：这两个信号仅在已使用F_SETOWN命令给相关套接字指派了属主后才会产生
        + F_SETOWN命令的整数类型arg参数既可以是一个正整数，指出接收信号的进程ID，也可以是一个负整数，其绝对值指出接收信号的进程组ID。F_GETOWN命令把套接字属主作为fcntl函数的返回值返回，它既可以是进程ID，也可以是进程组ID(一个除-1以外的负值)
        + 指定接收信号的套接字属主为一个进程或一个进程组的差别在于：前者仅导致单个进程接收信号，而后者则导致整个进程组中的所有进程接收信号
    - **F_GETOWN**：返回套接字的当前属主

例如，使用fcntl开启非阻塞式I/O对的典型代码如下：

```c
int flags;

if((flags = fcntl(fd,F_GETFL,0)) < 0)
    err_sys("F_GETFL error");
//设置某个文件状态标志的唯一正确的方法是：先取得当前标志，与新标志逻辑或后再设置标志
flags |= O_NONBLOCK;
if(fcntl(fd,F_SETFL,flags) < 0)
    err_sys("F_SETFL error");
```

## 2.套接字选项分类

**套接字选项粗分为两大基本类型**：

* 某个特性相关的**标志选项**
* 可以设置或检查的特定**值选项**

### 2.1 通用套接字选项

这些选项是协议无关的。它们由内核中的协议无关代码处理，而不是由诸如IPv4之类特殊的协议模块处理。不过其中有些选项只能应用到某些特定类型的套接字中。举例来说，尽管SO_BROADCAST套接字选项是“通用”的，它却只能应用于数据报套接字

#### 1）SO_ERROR(可以获取，不能设置)

当一个套接字上发生错误时，源自Berkeley的内核中的协议模块将该套接字的名为so_error的变量设为标准的Unix Exxx值中的一个，称它为套接字的待处理错误。内核会通知进程这个错误。进程然后可以通过该套接字选项获取so_error的值。由getsockopt返回的整数值就是该套接字的待处理错误。so_error随后由内核复位为0

#### 2）SO_KEEPALIVE

设置该选项后，如果2小时（可以通过修改内核来改这个时间）内在该套接字的任一方向上都没有数据交换，TCP就自动给对端发送一个“保持存活探测分节”。对端可以做出3种响应：

1. 以期望的ACK响应。应用进程得不到通知（因为一切正常） 
2. 响应RST分节，告知本端TCP：对端已崩溃且已重新启动。该套接字的待处理错误被置为ECONNRESET，套接字本身则被关闭
3. 没有任何响应（源自Berkeley的TCP将另外发送8个探测分节，两两相隔75s，试图得到一个响应。TCP在发出第一个探测分节后11分15秒内若没有得到任何响应则放弃），该套接字的待处理错误将被置为ETIMEOUT，套接字本身则被关闭；如果套接字收到一个ICMP错误作为某个探测分节的响应，那就返回相应的错误，套接字本身也被关闭（这种情形下一个场景ICMP错误是目的主机不得达，待处理错误会被置为EHOSTUNREACH）

#### 3）SO_LINGER

**该选项指定close函数对面向连接的协议如何操作**。默认操作是close函数立即返回，但是如果有数据残留在套接字发送缓冲区中，系统将试着把这些数据发送给对端。SO_LINGER套接字选项使得我们可以改变这个默认设置

选项要求在用户进程与内核间传递如下结构：

```c++
//头文件：<sys/socket.h>
struct linger{
	int l_onoff;   /* 0=off, nozero=on */
	int l_linger;  /* 延滞时间，POSIX指定单位为s */
};
```

对setsockopt的调用将根据其中两个结构成员的值形成下列3种情况之一：

1. **l_onoff为0**：此时l_linger值会被忽略。关闭该选项，默认设置生效，即close立即返回（**图7.7**）
2. **l_onoff非0，且l_linger为0**：TCP将终止连接，丢弃保留在套接字发送缓冲区中的任何数据，并发送一个RST给对端，而没有通常的四分组连接终止序列，这么一来避免了TIME_WAIT状态，然而存在以下可能性：在2MSL秒内创建该连接的另一个化身，导致来自刚被终止的连接上的旧的重复分节被不正确地传送到新的化身上
3. **l_onoff非0，且l_linger非0**：当套接字关闭时，内核将拖延一段时间。如果在套接字发送缓冲区中仍残留有数据，那么进程将投入睡眠，直到 a）所有数据都已经发送完且均被对方确认；b）延滞时间到；（如果套接字被设置为非阻塞，那么将不等待close完成，即使延滞时间非0也是如此）当使用SO_LINGER选项的这个特性时，应用进程检查close的返回值是非常重要的，因为如果在数据发送完并被确认前延滞时间到的话，close将返回EWOULDBLOCK错误，且套接字发送缓冲区中的任何残留数据都被丢弃。这种组合可能存在下列几种情况：
	* close直到数据和FIN已被服务器主机的TCP确认后才返回（问题是，在服务器应用进程读剩余数据之前，服务器主机可能崩溃，并且客户应用进程永远不会知道。因此，close成功返回只是告诉我们先前发送的数据(和FIN)已由对端TCP确认，而不能告诉我们对端应用进程是否已读取数据）（**图7.8**）
	* 延滞时间偏低，在接收到服务器主机的TCP确认前close返回（**图7.9**）

<div align="center"> <img src="../pic/unp-7-2.png"/> </div>

让客户知道服务器已读取其数据的一个方法是改为调用shutdown(并设置它的第二个参数为SHUT_WR)而不是调用close，并等待对端close连接的服务器端：

<div align="center"> <img src="../pic/unp-7-3.png"/> </div>

下图汇总了对shutdown的两种可能调用和对close的三种可能调用，以及它们对TCP套接字的影响：

<div align="center"> <img src="../pic/unp-7-4.png"/> </div>

#### 4）SO_RCVBUF和SO_SNDBUF

每个套接字都有一个发送缓冲区和一个接收缓冲区。这两个套接字选项允许我们改变这两个缓冲区的默认大小

* **TCP的流量控制**：对于TCP来说，套接字接收缓冲区中可用空间的大小限定了TCP通告对端的窗口大小。TCP套接字接收缓冲区不可能溢出，因为不允许对端发出超过本端所通告窗口大小的数据。如果对端无视窗口大小而发出了超过该窗口大小的数据，本端TCP将丢弃它们

* 对于UDP来说，当接收到的数据报装不进套接字接收缓冲区时，该数据报就被丢弃。UDP是没有流量控制的：较快的发送端可以很容易地淹没较慢的接收端，导致接收端的UDP丢弃数据报，事实上较快的发送端甚至可以淹没本机的网络接口，导致数据报被本机丢弃

**TCP的窗口规模选项是在建立连接时用SYN分节与对端互换得到的**：

* 对于客户，这意味着SO_RCVBUF选项必须在调用connect之前设置
* 对于服务器，这意味着该选项必须在调用listen之前给监听套接字设置

给已连接套接字设置该选项对于可能存在的窗口规模选项没有任何影响，因为accept直到TCP的三路握手完成才会创建并返回已连接套接字。这就是必须给监听套接字设置该选项的原因。（套接字缓冲区的大小总是由新创建的已连接套接字从监听套接字继承而来）

#### 5）SO_RCVLOWAT和SO_SNDLOWAT

每个套接字还有一个接收低水位标记和一个发送低水位标记。它们由select函数使用

* **接收低水位标记**是让select返回“可读”时套接字接收缓冲区中所需的数据量（对于TCP、UDP、SCTP套接字，其默认值是1）
* **发送低水位标记**是让select返回“可写”时套接字发送缓冲区中所需的可用空间（对于TCP套接字，其默认值通常是2048；UDP也使用发送低水位标记，然而由于UDP并不为应用程序传递给它的数据报保留副本，因此UDP套接字的发送缓冲区中可用空间的字节数从不改变，只要一个UDP套接字的发送缓冲区大小大于该套接字的低水位标记，该UDP套接字就总是可写的。UDP并没有发送缓冲区，只有发送缓冲区大小这个属性）

#### 6）SO_REUSEADDR和SO_REUSEPORT

**SO_REUSEADDR套接字选项能起到4个不同的功用**：

1. **允许启动一个监听服务器并捆绑其众所周知端口，即使以前建立的将该端口用作它们的本地端口的连接仍然存在**。这个条件通常是这样产生的：
    * a）启动一个监听服务器
    * b）连接请求到达，派生一个子进程来处理这个客户
    * c）监听服务器终止，但子进程继续为现有连接上的客户提供服务
    * d）重启监听服务 
2. **允许在同一端口上启动同一服务器的多个实例，只要每个实例捆绑一个不同的本地IP地址即可**
3. **允许单个进程捆绑同一端口到多个套接字上，只要每次捆绑指定不同的本地IP地址即可**
4. **允许完全重复的捆绑：当一个IP地址和端口已捆绑到某个套接字上时，如果传输协议支持，同样的IP地址和端口还可以捆绑到到另一个套接字上**（一般来说该特性仅支持UDP套接字，用于多播）

4.4BSD随多播支持的添加引入了SO_REUSEPORT这个套接字选项，它并未在SO_REUSEADDR上重载所需多播语义，而是引入了以下语义：

* 允许完全重复的捆绑，不过只有在想要捆绑同一IP地址和端口的每个套接字都指定了本套接字选项才行
* 如果被捆绑的IP地址时一个多播地址，那么SO_REUSEADDR和SO_REUSEPORT被认为是等效的

SO_REUSEPORT的问题在于并非所有系统都支持。在那些不支持该选项但是支持多播的系统上，改用SO_REUSEADDR以允许合理的完全重复的捆绑

> SO_REUSEADDR有一个潜在的安全问题。举例来说，假设存在一个绑定了通配地址和端口5555的套接字，如果指定SO_REUSEADDR，我们就可以把相同的端口捆绑到不同的IP地址上，譬如说就是所在主机的主IP地址。此后目的地端口为5555及新绑定IP地址的数据报将被递送到新的套接字，而不是递送到绑定了通配地址的已有套接字。这些数据报可以是TCP的SYN分节、STP的INIT块或UDP数据报。对于大多数众所周知的服务如HTTP、FTP和Telnet来说，这不成问题，因为这些服务器绑定的是保留端口。这种情况下，后来的试图捆绑这些端口更为明确的实例（也就是盗用这些端口）的任何进程都需要超级用户特权。然后NFS可能是一个问题，因为它的通常端口2049并不是保留端口

### 2.2 TCP套接字选项

TCP有两个套接字选项，他们的级别为IPPROTO_TCP

#### 1）TCP_MAXSEG

**该选项允许我们获取或设置TCP连接的最大分节大小(MSS)**。返回值是我们的TCP可以发送给对端的最大数据量，它通常是由对端使用SYN分节通告的MSS，除非我们的TCP选择使用一个比对端通告的MSS小些的值。如果该值在相应套接字的连接建立之前取得，那么返回值是未从对端收到MSS选项的情况下所用的默认值。（如果用上譬如说时间戳选项的话，那么实际用于连接中的最大分节大小可能小于该套接字选项的返回值，因为时间戳选项在每个分节中要占用12字节的TCP选项容量）

如果TCP支持路径MTU发现功能，那么它将发送的每个分节的最大数据量还可能在连接存活期内改变。如果到对端的路径发送变动，该值就会有所调整

#### 2）TCP_NODELAY

**开启该选项将禁止TCP的Nagle算法，默认情况下是启动的**

Nagle算法的目的在于防止一个连接在任何时刻有多个小分组待确认。如果某个给定连接上有待确认数据，那么原本应该作为用户写操作在该连接上立即发送相应小分组的行为就不会发生，直到现有数据被确认为止

考虑一个例子，在Rlogin或Telnet的客户端键入6个字符的串“hello!”，每个字符间间隔正好是250ms。到服务器端的RTT为600ms，而且服务器立即发回每个字符的回显。假设对客户端字符的ACK是和字符回显一同发回给客户端的，并且忽略客户端发送的对服务器端回显的ACK，下图展示了禁止Nagle算法和开启时的情况，在开启时，会感觉到明显的延迟：

<div align="center"> <img src="../pic/unp-7-5.png"/> </div>

Nagle算法常常与另一个TCP算法联合使用：**ACK延滞算法**，该算法使得TCP在接收到数据后不立即发送ACK，而是等待一小段时间（典型值为50ms~200ms），然后才发送ACK。TCP期待在这一小段时间内自身有数据发送回对端，被延滞的ACK就可以由这些数据捎带，从而省掉一个TCP分节（这种情形对于Rlogin和Telnet客户来说通常可行，因为他们的服务器一般都回显客户发送来的每个字符，这样对客户端字符的ACK完全可以在服务器对该字符的回显中捎带返回；然而对于服务器不在相反方向产生数据以便捎带ACK的客户来说，ACK延滞算法存在问题。这些客户可能觉察到明显的延迟）

<br>

# 六.名字与数值转换

**名字与数值间进行转换**：

* **主机名字与IP地址之间进行转换**（**协议相关**，只支持**IPv4**）：
    - **主机名字转IP地址**：[gethostbyname](#1gethostbyname函数)
    - **IP地址转主机名字**：[gethostbyaddr](#2gethostbyaddr函数)
* **服务名字与端口号之间进行转换**：
    - **服务名字**转**端口号**：[getservbyname](#1getservbyname函数)
    - **端口号**转**服务名字**：[getservbyport](#2getservbyport函数)
* **主机与服务名字**转**IP地址与端口号**：
    - [getaddrinfo](#1getaddrinfo函数)（**协议无关**）
    - getaddrinfo的封装函数:
        + [host_serv](#2host_serv函数)
        + [tcp_connect](#3tcp_connect函数)
        + [tcp_listen](#4tcp_listen函数)
        + [udp_client](#5udp_client函数)
        + [udp_connect](#6udp_connect函数)
        + [udp_server](#7udp_server函数)
* **IP地址与端口号**转**主机与服务名字**：[getnameinfo](#getnameinfo函数)

## 1.主机名字与IP地址之间的转换

**可以通过DNS获取名字和地址信息**

<div align="center"> <img src="../pic/unp-name-1.png"/> </div>

* 解析器代码通过读取其系统相关配置文件(通常是**/etc/resolv.conf**)确定本组织机构的名字服务器的所在位置
* 解析器使用UDP向本地名字服务器发出查询，如果本地名字服务器不知道答案，通常会使用UDP在整个因特网上查询其它名字服务器（如果答案太长，超出了UDP消息的承载能力，本地名字服务器和解析器会自动切换到TCP）

**不使用DNS也可能获取名字和地址信息，有下列替代方法**：

1. 静态主机文件（通常是**/etc/hosts**文件）
2. 网络信息系统（NIS）
3. 轻权目录访问协议（LDAP）

系统管理员如何配置一个主机以使用不同类型的名字服务是实现相关的，但这些差异对开发人员来说，通常是透明的，只需调用诸如gethostbyname和gethostbyaddr这样的解析器函数

### 1）gethostbyname函数

<div align="center"> <img src="../pic/unp-name-2.png"/> </div>

函数的局限是**只能返回IPv4地址**，返回的指针指向hostent结构，该结构含有所查找主机的所有IPv4地址：

```c++
struct hostent{
    char *h_name;           //规范主机名
    char **h_aliases;       //主机别名
    int h_addrtype;         //主机地址类型：AF_INET
    int h_length;           //地址长度：4
    char **h_addr_list;     //IPv4地址
};
```

<div align="center"> <img src="../pic/unp-name-3.png"/> </div>

当发生错误时，函数会设置全局变量h_errno为定义在\<netdb.h\>中的下列常值：

* **HOST_NOT_FOUND**：
* **TRY_AGAIN**：
* **NO_RECOVERY**：
* **NO_DATA**(等同于**NO_ADDRESS**)：表示指定的名字有效，但没有A记录（只有MX记录的主机名就是这样的一个例子）

如今多数解析器提供hstrerror函数，该函数以某个h_errno值作为唯一参数，返回一个指向相应错误说明的const char *指针

### 2）gethostbyaddr函数

该函数试图由一个二进制的IP地址找到相应的主机名，与gethostbyname的行为相反

<div align="center"> <img src="../pic/unp-name-4.png"/> </div>

* **addr**：实际上是一个指向存放IPv4地址的某个in_addr结构的指针
* **len**：addr指向的in_addr结构的大小（对于IPv4地址为4）
* **family**：AF_INET

函数同样返回一个指向hostent结构的指针，但是不同于gethostbyname，这里我们感兴趣的通常是存放规范主机名的h_name字段

## 2.服务名字与端口号之间的转换

### 1）getservbyname函数

从服务名字到端口的映射关系通常保存在**/etc/services**文件中，因此如果程序中使用服务名字而非端口号时，即使端口号发生变动，仅需修改这个文件，而不必重新编译应用程序

<div align="center"> <img src="../pic/unp-name-5.png"/> </div>

* **servname**：服务名参数，必须指定
* **protoname**：协议，如果指定了，那么指定的服务必须有匹配的协议（如果protoname未指定而servname服务支持多个协议，那么返回哪个端口号取决于实现）

函数成功时返回指向servent结构的指针：

```c++
struct servent{
    char *s_name;       //规范服务名
    char **s_aliases;   //服务别名
    int s_port;         //服务对应的端口号（网络字节序）
    char *s_proto;      //使用的协议
};
```

### 2）getservbyport函数

<div align="center"> <img src="../pic/unp-name-6.png"/> </div>

* **port**：端口号，必须为网络字节序
* **protoname**：指定协议（有些端口号在TCP上用于一种服务，在UDP上却用于完全不同的另一种服务）

## 3.主机与服务名字转IP地址与端口号

### 1）getaddrinfo函数

getaddrinfo与协议无关，并且能处理**名字到地址**、**服务到端口**这两种转换。返回的不再是地址列表，返回的addrinfo结构中包含了一个指向sockaddr结构的指针，这些sockaddr结构随后可由套接字函数直接使用，因此将协议相关性完全隐藏在函数的内部

<div align="center"> <img src="../pic/unp-name-7.png"/> </div>

* **hostname**：主机名或IP地址串
* **service**：服务名或端口号数串
* **hints**：可以是空指针。非空时指向的addrinfo结构包含了一些对期望返回的信息类型的限制
* **result**：指向addrinfo结构的指针，**返回值**
    * 如果与hostname参数关联的地址有多个，那么适用于所请求地址族的每个地址都返回一个对应的结构
    * 如果service参数指定的服务支持多个套接字类型，那么每个套接字类型都可能返回一个对应的结构

```c++
//调用者可以通过hints设置的字段有：ai_flags、ai_family、ai_socktype、ai_protocol
//如果hints参数是一个空指针，函数就假设ai_flags、ai_family、ai_socktype为0，ai_protocol为AF_UNSPEC
struct addrinfo{
    int ai_flags;               //0个或多个或在一起的AI_xxx值
    int ai_family;              //某个AF_xxx值
    int ai_socktype;            //某个SOCK_xxx值
    int ai_protocol;            //0或IPPROTO_xxx
    socklen_t ai_addrlen;       //ai_addr的长度
    char *ai_canonname;         //指向规范主机名的指针
    struct sockaddr *ai_addr;   //指向套接字地址结构的指针
    struct addrinfo *ai_next;   //指向链表中下一个addrinfo结构的指针
};

//ai_flags成员可用的标志值及含义如下：
AI_PASSIVE：套接字将用于被动打开
AI_CANONNAME：告知getaddrinfo函数返回主机的规范名字
AI_NUMERICHOST：防止任何类型的名字到地址映射，hostname参数必须是一个地址串
AI_NUMERICSERV：防止任何类型的名字到服务映射，service参数必须是一个十进制端口号数串
AI_V4MAPPED：如果同时指定ai_family的值为AF_INET6，那么如果没有可用的AAAA记录，就返回与A记录对应的IPv4映射的IPv6地址
AI_ALL：如果同时指定了AI_V4MAPPED，那么返回与AAAA记录对应的IPv6地址、与A记录对于的IPv4映射的IPv6地址
AI_ADDRCONFIG：按照所在主机的配置选择返回地址类型
```

如果函数成功，result指向的变量已被填入一个指针，指向的是由ai_next成员串起来的addrinfo结构链表（这些结构的先后顺序没有保证）：

<div align="center"> <img src="../pic/unp-name-8.png"/> </div>

常见的使用：

* **TCP或UDP客户同时制定hostname和service**
    - **TCP客户**在一个循环中针对每个返回的IP地址，逐一调用socket和connect，直到有一个连接成功，或者所有地址尝试完毕
    - 对于**UDP客户**，由getaddrinfo填入的套接字地址结构用于调用sendto或connect。如果客户能够判断第一个地址看来不工作（或者在已连接的UDP套接字上收到出错消息，或者在未连接的套接字上经历消息接收超时），那么可以尝试其余地址
* **典型的服务器只指定service而不指定hostname，同时在hints结构中指定AI_PASSIVE标志**。返回的套接字地址结构中应含有一个值为INADDR_ANY(对于IPv4)或IN6ADDR_ANY_INIT(对于IPv6)的IP地址
    - 函数返回后，**TCP服务器**调用socket、bind和listen。如果服务器想要malloc另一个套接字地址结构以从accept获取客户的地址，那么返回的ai_addrlen值给出了这个套接字地址结构的大小
    - **UDP服务器**将调用socket、bind和recvfrom。如果想要malloc另一个套接字地址结构以从recvfrom获取客户的地址，那么返回的ai_addrlen值给出了这个套接字地址结构的大小
    - 以上假设服务器仅处理一个套接字，如果**使用select或poll让服务器处理多个套接字**，服务器将遍历由getaddrinfo返回的整个addrinfo结构链表，并为每个结构创建一个套接字，再使用select或poll

如果**客户或服务器**清楚自己只处理一种类型的套接字，那么应该把hints结构的ai_socktype成员设置成SOCK_STREAM或SOCK_DGRAM

如果发生**错误**，函数getaddrinfo返回错误值，该值可以作为函数**gai_strerror()**的参数。调用gai_strerror函数可以得到一个描述错误信息的C字符串指针：

<div align="center"> <img src="../pic/unp-name-9.png"/> </div>

常见的错误说明如下表：

<div align="center"> <img src="../pic/unp-name-10.png"/> </div>

getaddrinfo函数返回的所有**存储空间都是动态获取**的，包括addrinfo结构、ai_addr结构和ai_canonname字符串，可以通过调用**freeaddrinfo**返**还给系统**：

<div align="center"> <img src="../pic/unp-name-11.png"/> </div>

* **ai**：指向由getaddrinfo返回的第一个addrinfo结构（这个链表中所有的结构以及由它们指向的任何动态存储空间都被释放掉）

> 尽管getaddrinfo函数确实比gethostbyname和getservbyname要“好”：1）能编写协议无关的代；2）单个函数能同时处理主机名和服务名；3）所有返回信息动态分配而非静态分配；但是它仍没有像期待的那样好用：必须先分配一个hints结构，把它清零后填写需要的字段，再调用getaddrinfo，然后遍历一个链表逐一尝试每个返回地址

### 2）host_serv函数

host_serv封装了函数getaddrinfo，不要求调用者分配并填写一个hints结构，该结构中的**地址族**和**套接字类型**字段作为参数：

<div align="center"> <img src="../pic/unp-name-12.png"/> </div>

[函数源码](https://github.com/arkingc/unpv13e/blob/master/lib/host_serv.c#L4)

### 3）tcp_connect函数

tcp_connect执行TCP客户的通常步骤：创建一个TCP套接字并连接到一个服务器

<div align="center"> <img src="../pic/unp-name-13.png"/> </div>

[函数源代码](https://github.com/arkingc/unpv13e/blob/master/lib/tcp_connect.c#L5)

[时间获取程序——使用tcp_connect的客户端](https://github.com/arkingc/unpv13e/blob/master/names/daytimetcpcli.c)

### 4）tcp_listen函数

tcp_listen执行TCP服务器的通常步骤：创建一个TCP套接字，给它捆绑服务器的众所周知的端口，并允许接受外来的连接请求：

<div align="center"> <img src="../pic/unp-name-14.png"/> </div>

[函数源代码](https://github.com/arkingc/unpv13e/blob/master/lib/tcp_listen.c#L5)

* [时间获取程序——使用tcp_listen的服务器](https://github.com/arkingc/unpv13e/blob/master/names/daytimetcpsrv1.c)（不可指定协议）
* [时间获取程序——使用tcp_listen的服务器](https://github.com/arkingc/unpv13e/blob/master/names/daytimetcpsrv2.c)（可指定协议）

### 5）udp_client函数

创建未连接UDP套接字：

<div align="center"> <img src="../pic/unp-name-15.png"/> </div>

* **saptr**：指向的套接字地址结构保存有服务器的IP地址和端口号，用于稍后调用sendto
* **lenp**：saptr所指的套接字地址结构的大小。不能为空指针，因为任何sendto和recvfrom调用都需要知道套接字地址结构的长度

[函数源代码](https://github.com/arkingc/unpv13e/blob/master/lib/udp_client.c#L5)

[时间获取程序——使用udp_client的客户端](https://github.com/arkingc/unpv13e/blob/master/names/daytimeudpcli1.c)（可指定协议）

### 6）udp_connect函数

创建一个已连接UDP套接字：

<div align="center"> <img src="../pic/unp-name-16.png"/> </div>

因为已连接套接字改用write代替sendto，所以相比于udp_client，省略了套接字地址结构及长度参数

[函数源代码](https://github.com/arkingc/unpv13e/blob/master/lib/udp_connect.c#L5)

### 7）udp_server函数

<div align="center"> <img src="../pic/unp-name-17.png"/> </div>

[时间获取程序——使用udp_server的服务器](https://github.com/arkingc/unpv13e/blob/master/names/daytimeudpsrv2.c)（可指定协议）

## 4.IP地址与端口号转主机与服务名字

### getnameinfo函数

getaddrinfo的互补函数

<div align="center"> <img src="../pic/unp-name-18.png"/> </div>

* **sockaddr**：指向套接字地址结构，包含了待转换为可读字符串的协议地址
* **addrlen**：sockaddr指向的套接字地址结构的大小
* **host**：指向存储转换得到的”主机名“信息的buf（调用者预先分配）
* **hostlen**：host指向的buf的大小（不想获得”主机名“信息则设为0）
* **serv**：指向存储转换得到的”服务名“信息的buf（调用者预先分配）
* **servlen**：serv指向的buf的大小（不想获得”服务名“信息则设为0）
* **flags**：标志，见下表

<div align="center"> <img src="../pic/unp-name-19.png"/> </div>

> getnameinfo和sock_ntop的差别在于：sock_ntop不涉及DNS

## 5.其它网络相关信息

应用进程可能想要查找4类与网络相关的信息：**主机**、**网络**、**协议**、**服务**。大多数查找针对的是主机，一小部分查找针对的是服务，更小一部分查找针对的是网络和协议。所有4类信息都可以放在一个文件中，每类信息各定义有3个访问函数：

1. 函数getXXXent读出文件中的下一个表项，必要的话首先打开文件
2. 函数setXXXent打开（如果尚未打开的话）并回绕文件
3. 函数endXXXent关闭文件

每类信息都定义了各自的结构：hostent、netent、protoent、servent。这些结构定义在头文件<netdb.h>中

<div align="center"> <img src="../pic/unp-name-20.png"/> </div>

* **只有主机和网络信息可通过DNS获取**，协议和服务信息总是从相应文件中读取
* 如果使用DNS查找主机和网络信息，只有键值查找函数才有意义。如果调用gethostent，那么它仅仅读取/etc/hosts文件并避免访问DNS

<br>

# 附1.回射服务器程序

## 1.TCP回射服务器程序

<table>
<tr>
    <td rowspan="10" align="center"> <b>TCP回射服务器</b> </td>
    <td rowspan="2" align="center"> v1 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/tcpcliserv/tcpcli01.c">客户端</a> </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/lib/str_cli.c">str_cli函数</a>(阻塞于标准输入时无法处理来自服务器子进程的FIN分节) </td>
</tr>
<tr>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/tcpcliserv/tcpserv01.c">服务器</a>(多进程) </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/znote/TCP%E5%9B%9E%E5%B0%84%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%9A%84%E9%97%AE%E9%A2%98.md#1%E5%AE%A2%E6%88%B7%E7%AB%AF%E6%AD%A3%E5%B8%B8%E7%BB%88%E6%AD%A2">服务器会产生僵尸子进程</a> </td>
</tr>
<tr>
    <td rowspan="1" align="center"> v2 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/tcpcliserv/tcpserv02.c">服务器</a>(多进程) </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/znote/TCP%E5%9B%9E%E5%B0%84%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%9A%84%E9%97%AE%E9%A2%98.md#11-%E4%BD%BF%E7%94%A8wait%E7%89%88sig_chld%E5%87%BD%E6%95%B0%E5%A4%84%E7%90%86%E5%AD%90%E8%BF%9B%E7%A8%8Bsigchld%E4%BF%A1%E5%8F%B7">处理服务器僵尸子进程，会中断服务器系统调用</a> </td>
</tr>
<tr>
    <td rowspan="1" align="center"> v3 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/tcpcliserv/tcpserv03.c">服务器</a>(多进程) </td>
    <td align="center"> 处理服务器被中断的系统调用，无法同时处理多个SIGCHLD信号 </td>
</tr>
<tr>
    <td rowspan="2" align="center"> v4 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/tcpcliserv/tcpcli04.c">客户端</a> </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/znote/TCP%E5%9B%9E%E5%B0%84%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%9A%84%E9%97%AE%E9%A2%98.md#12-%E4%BD%BF%E7%94%A8waitpid%E7%89%88sig_chld%E5%87%BD%E6%95%B0%E5%A4%84%E7%90%86%E5%AD%90%E8%BF%9B%E7%A8%8Bsigchld%E4%BF%A1%E5%8F%B7">正常终止时引起服务器5个子进程终止</a> </td>
</tr>
<tr>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/tcpcliserv/tcpserv04.c">服务器</a>(多进程) </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/znote/TCP%E5%9B%9E%E5%B0%84%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%9A%84%E9%97%AE%E9%A2%98.md#12-%E4%BD%BF%E7%94%A8waitpid%E7%89%88sig_chld%E5%87%BD%E6%95%B0%E5%A4%84%E7%90%86%E5%AD%90%E8%BF%9B%E7%A8%8Bsigchld%E4%BF%A1%E5%8F%B7">同时处理多个SIGCHLD信号</a> </td>
</tr>
<tr>
    <td rowspan="3" align="center"> select </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/select/tcpcli01.c">客户端</a> </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/select/strcliselect01.c">str_cli函数</a>(解决v1版的问题，但无法处理重定向、无法处理I/O缓冲) </td>
</tr>
<tr>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/select/tcpcli02.c">客户端</a> </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/select/strcliselect02.c">str_cli函数</a>(解决前一版的问题) </td>
</tr>
<tr>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/znote/select.md#%E4%BB%A3%E7%A0%81">服务器</a>(单进程) </td>
    <td align="center"> 重写v4版服务器，使用单进程减少了多进程的开销 </td>
</tr>
<tr>
    <td rowspan="1" align="center"> poll </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/tcpcliserv/tcpservpoll01.c">服务器</a>(单进程) </td>
    <td align="center"> 重写v4版服务器，使用单进程减少了多进程的开销 </td>
</tr>

<tr>
    <td align="center"> <b>总结</b> </td>
    <td colspan="3" align="center"> <b>v1-v4：正确处理服务器终止的子进程</b> </td>
</tr>
</table>

## 2.UDP回射服务器程序

<table>
<tr>
    <td rowspan="7" align="center"> <b>UDP回射服务器</b> </td>
    <td rowspan="2" align="center"> v1 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/udpcli01.c">客户端</a> </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/lib/dg_cli.c">dg_cli函数</a>(v1)<br>问题一：任何进程可向客户端发数据，会与服务器的回射数据报混杂<br>问题二：客户数据报或服务器应答丢失会使客户永久阻塞于recvfrom<br>
    <a href = "https://github.com/arkingc/unpv13e/blob/master/znote/UDP%E5%9B%9E%E5%B0%84%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%9A%84%E9%97%AE%E9%A2%98.md#2%E6%9C%8D%E5%8A%A1%E5%99%A8%E8%BF%9B%E7%A8%8B%E6%9C%AA%E8%BF%90%E8%A1%8C">问题三：服务器未启动会使客户端阻塞于recvfrom</a></td>
</tr>
<tr>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/udpserv01.c">服务器</a>(单进程) </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/lib/dg_echo.c">dg_echo函数</a> </td>
</tr>
<tr>
    <td rowspan="1" align="center"> v2 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/udpcli02.c">客户端</a> </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/dgcliaddr.c">dg_cli函数</a>(v2)<br> <a href = "https://github.com/arkingc/unpv13e/blob/master/znote/UDP%E5%9B%9E%E5%B0%84%E6%9C%8D%E5%8A%A1%E5%99%A8%E7%9A%84%E9%97%AE%E9%A2%98.md#11-%E9%AA%8C%E8%AF%81%E6%94%B6%E5%88%B0%E7%9A%84%E6%95%B0%E6%8D%AE">处理问题一，验证接收到的响应。但无法处理服务器多宿(多个IP)的情况</a> </td>
</tr>
<tr>
    <td rowspan="1" align="center"> v3 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/udpcli04.c">客户端</a>(connect版) </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/dgcliconnect.c">dg_cli函数</a>(v3)<br> </td>
</tr>
<tr>
    <td rowspan="2" align="center"> v4 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/udpcli06.c">客户端</a> </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/dgcliloop1.c">dg_cli函数</a>(v4)：写2000个1400字节的UDP数据报给服务器<br>问题：UDP缺乏流量控制，服务器接收速率慢时，缓冲区被发送端淹没<br></td>
</tr>
<tr>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/udpserv06.c">服务器</a>(单进程) </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/dgecholoop1.c">dg_echo函数</a> </td>
</tr>
<tr>
    <td rowspan="1" align="center"> v5 </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/udpserv07.c">服务器</a>(单进程) </td>
    <td align="center"> <a href = "https://github.com/arkingc/unpv13e/blob/master/udpcliserv/dgecholoop2.c">dg_echo函数</a>(增大接收缓冲区的大小)</td>
</tr>
<tr>
    <td align="center"> <b>总结</b> </td>
    <td colspan="3" align="center"> <b>v1：问题二、三的根本原因是UDP数据传输不可靠</b><br><b>v4-v5：UDP缺乏流量控制，服务器接收的数据报数目不定，依赖诸多因素</b>  </td>
</tr>
</table>

# 附2.头文件映射表

## 1.类型与头文件映射表

<table>
<tr>
    <td rowspan="6"> 整形 </td>
    <td rowspan="6"> &lt;sys/types.h&gt; </td>
    <td> int8_t </td>
    <td> 带符号的8位整数 </td>
</tr>
<tr>
    <td> uint8_t </td>
    <td> 无符号的8位整数 </td>
</tr>
<tr>
    <td> int16_t </td>
    <td> 带符号的16位整数 </td>
</tr>
<tr>
    <td> uint16_t </td>
    <td> 无符号的16位整数 </td>
</tr>
<tr>
    <td> int32_t </td>
    <td> 带符号的32位整数 </td>
</tr>
<tr>
    <td> uint32_t </td>
    <td> 无符号的32位整数 </td>
</tr>

<tr>
    <td rowspan="2"> 时间 </td>
    <td rowspan="1"> &lt;sys/time.h&gt; </td>
    <td> timeval </td>
    <td> 时间结构，包含“秒”和“微妙”成员 </td>
</tr>
<tr>
    <td rowspan="1"> &lt;time.h&gt; </td>
    <td> timespec </td>
    <td> 时间结构，包含“秒”和“纳秒”成员 </td>
</tr>

<tr>
    <td rowspan="8"> 套接字地址结构相关 </td>
   <td rowspan="3"> &lt;sys/socket.h&gt; </td>
    <td> <b>sockaddr</b> </td>
   <td> <b>通用套接字地址结构</b> </td>
</tr>
<tr>
   <td> sa_family_t </td>
   <td> 套接字地址结构的地址族 </td>
</tr>
<tr>
    <td> socklen_t </td>
    <td> 套接字地址结构的长度，一般为uint32_t  </td>
</tr>
<tr>
    <td rowspan="5"> &lt;netinet/in.h&gt; </td>
   <td> <b>sockaddr_in</b> </td>
    <td> <b>IPv4套接字地址结构</b> </td> 
</tr>
<tr>
    <td> <b>sockaddr_in6</b> </td>
    <td> <b>IPv6套接字地址结构</b> </td>   
</tr>
<tr>
    <td> <b>sockaddr_storage</b> </td>
    <td> <b>新版通用套接字地址结构</b> </td>
</tr>
<tr>
    <td> in_addr_t </td>
   <td> IPv4地址，一般为uint32_t </td>
</tr>
<tr>
    <td> in_port_t </td>
    <td> TCP或UDP端口，一般为uint16_t </td>
</tr>
</table>

## 2.函数与头文件映射表

<table>
<tr>
    <td rowspan="6"> <b>字节操纵</b> </td>
    <td rowspan="3"> &lt;strings.h&gt; </td>
    <td> <b>bzero</b> </td>
</tr>
<tr>
    <td> <b>bcopy</b> </td>
</tr>
<tr>
    <td> <b>bcmp</b> </td>
</tr>
<tr>
    <td rowspan="3"> &lt;string.h&gt; </td>
    <td> <b>memset</b> </td>
</tr>
<tr>
    <td> <b>memcpy</b></td>
</tr>
<tr>
    <td> <b>memcmp</b> </td>
</tr>

<tr>
    <td rowspan="4"> <b>字节序转换</b> </td>
    <td rowspan="4"> &lt;netinet/in.h&gt; </td>
    <td> <b>htons</b> </td>
</tr>
<tr>
    <td> <b>htonl</b> </td>
</tr>
<tr>
    <td> <b>ntohs</b> </td>
</tr>
<tr>
    <td> <b>ntohl</b> </td>
</tr>

<tr>
    <td rowspan="5"> <b>地址转换</b> </td>
    <td rowspan="5"> &lt;arpa/inet.h&gt; </td>
    <td> <b>inet_aton</b> </td>
</tr>
<tr>
    <td> <b>inet_addr</b> </td>
</tr>
<tr>
    <td> <b>inet_ntoa</b> </td>
</tr>
<tr>
    <td> <b>inet_pton</b> </td>
</tr>
<tr>
    <td> <b>inet_ntop</b> </td>
</tr>

<tr>
    <td rowspan="10"> <b>基本套接字编程</b> </td>
    <td rowspan="9"> &lt;sys/socket.h&gt; </td>
    <td> <a href="#1socket函数">socket</a> </td>
</tr>
<tr>
    <td> <a href="#2connect函数">connect</a> </td>
</tr>
<tr>
    <td> <a href="#3bind函数">bind</a> </td>
</tr>
<tr>
    <td> <a href="#4listen函数">listen</a> </td>
</tr>
<tr>
    <td> <a href="#5accept函数">accept</a> </td>
</tr>
<tr>
    <td> <a href="#1recvfrom与sendto函数">recvfrom</a> </td>
</tr>
<tr>
    <td> <a href="#1recvfrom与sendto函数">sendto</a> </td>
</tr>
<tr>
    <td> <a href="#7getsockname和getpeername函数">getsockname</a> </td>
    <td> <b>根据套接字获取本地协议地址</b> </td>
</tr>
<tr>
    <td> <a href="#7getsockname和getpeername函数">getpeername</a> </td>
    <td> <b>根据套接字获取外地协议地址</b> </td>
</tr>
<tr>
    <td rowspan="1"> &lt;unistd.h&gt; </td>
    <td> <a href="#6close函数">close</a> </td>
</tr>

<tr>
    <td rowspan="6"> <b>I/O复用</b> </td>
    <td rowspan="2"> &lt;sys/select.h&gt; </td>
    <td> <b>select</b> </td>
</tr>
<tr>
    <td> <b>pselect</b> </td>
</tr>
<tr>
    <td rowspan="1"> &lt;sys/poll.h&gt; </td>
    <td> <b>poll</b> </td>
</tr>
<tr>
    <td rowspan="3"> &lt;sys/epoll.h&gt; </td>
    <td> <b>epoll_create</b> </td>
</tr>
<tr>
    <td> <b>epoll_ctl</b> </td>
</tr>
<tr>
    <td> <b>epoll_wait</b> </td>
</tr>

<tr>
    <td rowspan="6"> <b>名字与数值转换</b> </td>
    <td rowspan="6"> &lt;netdb.h&gt; </td>
    <td> <a href="#1gethostbyname函数">gethostbyname</a> </td>
    <td> <b>主机名字转IP地址(只支持IPv4)</b> </td>
</tr>
<tr>
    <td> <a href="#2gethostbyaddr函数">gethostbyaddr</a> </td>
    <td> <b>IP地址转主机名字(只支持IPv4)</b> </td>
</tr>
<tr>
    <td> <a href="#1getservbyname函数">getservbyname</a> </td>
    <td> <b>服务名字转端口号</b> </td>
</tr>
<tr>
    <td> <a href="#2getservbyport函数">getservbyport</a> </td>
    <td> <b>端口号转服务名字</b> </td>
</tr>
<tr>
    <td> <a href="#1getaddrinfo函数">getaddrinfo</a> </td>
    <td> <b>主机与服务名字转IP地址与端口号</b> </td>
</tr>
<tr>
    <td> <a href="#getnameinfo函数">getnameinfo</a> </td>
    <td> <b>IP地址与端口号转主机与服务名字</b> </td>
</tr>
</table>

# 七.高级I/O函数

## 1.套接字超时

套接字I/O操作上设置超时的方法有3种：

1. 调用alarm，它再指定超时期满时产生SIGALRM信号。**但**涉及信号处理，信号处理在不同实现上存在差异，而且可能干扰进程中现有的alarm信号（**适用于任何描述符**）
2. 在select中阻塞等待I/O，以此替代直接阻塞在read或write调用上（**适用于任何描述符**）
3. 使用较新的SO_RCVTIMEO和SO_SNDTIMEO套接字选项。**但**并非所有实现都支持这两个套接字选项（**仅使用于套接字描述符**）
    * SO_RCVTIMEO仅应用于(该描述符上的所有)读操作
    * SO_SNDTIMEO仅应用于(该描述符上的所有)写操作

上述3个技术都适用于输入和输出操作（read、write、recvfrom、sendto等）。但是对于connect（connect的**内置超时相当长，典型值为75s**）：

* [alarm可以为connect设置超时](https://github.com/arkingc/unpv13e/blob/master/lib/connect_timeo.c#L7)，但：
    - 总能减少connect的超时期限，但是无法延长内核现有的超时期限（比如能比75小，但是不能更大）
    - 使用了系统调用的可中断能力，使得它们能够在内核超时发生之前返回，前提是：执行的是系统调用，并且能够直接处理由它们返回的EINTR错误
    - 在多线程中正确使用信号非常困难
* select用来在connect上设置超时的先决条件是相应套接字处于非阻塞模式
* 3中的两个套接字选项对connect不适用

使用3种套接字超时技术处理UDP客户端永久阻塞于recvfrom的问题：

* [使用SIGALRM为recvfrom设置超时](https://github.com/arkingc/unpv13e/blob/master/advio/dgclitimeo3.c#L6)
* [使用select为recvfrom设置超时](https://github.com/arkingc/unpv13e/blob/master/advio/dgclitimeo1.c#L4)（[readable_timeo函数](https://github.com/arkingc/unpv13e/blob/master/lib/readable_timeo.c#L5)）
* [使用SO_RCVTIMEO套接字选项为recvfrom设置超时](https://github.com/arkingc/unpv13e/blob/master/advio/dgclitimeo2.c#L4)

