/*
 * Copyright (c) 1996-1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_ALLOC_H
#define __SGI_STL_INTERNAL_ALLOC_H

#ifdef __SUNPRO_CC
#  define __PRIVATE public
   // Extra access restrictions prevent us from really making some things
   // private.
#else
#  define __PRIVATE private
#endif

#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
#  define __USE_MALLOC
#endif


// This implements some standard node allocators.  These are
// NOT the same as the allocators in the C++ draft standard or in
// in the original STL.  They do not encapsulate different pointer
// types; indeed we assume that there is only one pointer type.
// The allocation primitives are intended to allocate individual objects,
// not larger arenas as with the original STL allocators.

#if 0
#   include <new>
#   define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#   include <iostream.h>
#   define __THROW_BAD_ALLOC cerr << "out of memory" << endl; exit(1)
#endif

#ifndef __ALLOC
#   define __ALLOC alloc
#endif
#ifdef __STL_WIN32THREADS
#   include <windows.h>
#endif

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifndef __RESTRICT
#  define __RESTRICT
#endif

#if !defined(__STL_PTHREADS) && !defined(_NOTHREADS) \
 && !defined(__STL_SGI_THREADS) && !defined(__STL_WIN32THREADS)
#   define _NOTHREADS
#endif

# ifdef __STL_PTHREADS
    // POSIX Threads
    // This is dubious, since this is likely to be a high contention
    // lock.   Performance may not be adequate.
#   include <pthread.h>
#   define __NODE_ALLOCATOR_LOCK \
        if (threads) pthread_mutex_lock(&__node_allocator_lock)
#   define __NODE_ALLOCATOR_UNLOCK \
        if (threads) pthread_mutex_unlock(&__node_allocator_lock)
#   define __NODE_ALLOCATOR_THREADS true
#   define __VOLATILE volatile  // Needed at -O3 on SGI
# endif
# ifdef __STL_WIN32THREADS
    // The lock needs to be initialized by constructing an allocator
    // objects of the right type.  We do that here explicitly for alloc.
#   define __NODE_ALLOCATOR_LOCK \
        EnterCriticalSection(&__node_allocator_lock)
#   define __NODE_ALLOCATOR_UNLOCK \
        LeaveCriticalSection(&__node_allocator_lock)
#   define __NODE_ALLOCATOR_THREADS true
#   define __VOLATILE volatile  // may not be needed
# endif /* WIN32THREADS */
# ifdef __STL_SGI_THREADS
    // This should work without threads, with sproc threads, or with
    // pthreads.  It is suboptimal in all cases.
    // It is unlikely to even compile on nonSGI machines.

    extern "C" {
      extern int __us_rsthread_malloc;
    }
	// The above is copied from malloc.h.  Including <malloc.h>
	// would be cleaner but fails with certain levels of standard
	// conformance.
#   define __NODE_ALLOCATOR_LOCK if (threads && __us_rsthread_malloc) \
                { __lock(&__node_allocator_lock); }
#   define __NODE_ALLOCATOR_UNLOCK if (threads && __us_rsthread_malloc) \
                { __unlock(&__node_allocator_lock); }
#   define __NODE_ALLOCATOR_THREADS true
#   define __VOLATILE volatile  // Needed at -O3 on SGI
# endif
# ifdef _NOTHREADS
//  Thread-unsafe
#   define __NODE_ALLOCATOR_LOCK
#   define __NODE_ALLOCATOR_UNLOCK
#   define __NODE_ALLOCATOR_THREADS false
#   define __VOLATILE
# endif

__STL_BEGIN_NAMESPACE

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1174
#endif

// Malloc-based allocator.  Typically slower than default alloc below.
// Typically thread-safe and more storage efficient.
#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
# ifdef __DECLARE_GLOBALS_HERE
    void (* __malloc_alloc_oom_handler)() = 0;
    // g++ 2.7.2 does not handle static template data members.
# else
    extern void (* __malloc_alloc_oom_handler)();
# endif
#endif

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

typedef __malloc_alloc_template<0> malloc_alloc;

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

// Allocator adaptor to check size arguments for debugging.
// Reports errors using assert.  Checking can be disabled with
// NDEBUG, but it's far better to just use the underlying allocator
// instead when no checking is desired.
// There is some evidence that this can confuse Purify.
template <class Alloc>
class debug_alloc {

private:

enum {extra = 8};       // Size of space used to store size.  Note
                        // that this must be large enough to preserve
                        // alignment.

public:

static void * allocate(size_t n)
{
    char *result = (char *)Alloc::allocate(n + extra);
    *(size_t *)result = n;
    return result + extra;
}

static void deallocate(void *p, size_t n)
{
    char * real_p = (char *)p - extra;
    assert(*(size_t *)real_p == n);
    Alloc::deallocate(real_p, n + extra);
}

static void * reallocate(void *p, size_t old_sz, size_t new_sz)
{
    char * real_p = (char *)p - extra;
    assert(*(size_t *)real_p == old_sz);
    char * result = (char *)
                  Alloc::reallocate(real_p, old_sz + extra, new_sz + extra);
    *(size_t *)result = new_sz;
    return result + extra;
}


};


# ifdef __USE_MALLOC

typedef malloc_alloc alloc;
typedef malloc_alloc single_client_alloc;

# else


// Default node allocator.
// With a reasonable compiler, this should be roughly as fast as the
// original STL class-specific allocators, but with less fragmentation.
// Default_alloc_template parameters are experimental and MAY
// DISAPPEAR in the future.  Clients should just use alloc for now.
//
// Important implementation properties:
// 1. If the client request an object of size > __MAX_BYTES, the resulting
//    object will be obtained directly from malloc.
// 2. In all other cases, we allocate an object of size exactly
//    ROUND_UP(requested_size).  Thus the client has enough size
//    information that we can return the object to the proper free list
//    without permanently losing part of the object.
//

// The first template parameter specifies whether more than one thread
// may use this allocator.  It is safe to allocate an object from
// one instance of a default_alloc and deallocate it with another
// one.  This effectively transfers its ownership to the second one.
// This may have undesirable effects on reference locality.
// The second parameter is unreferenced and serves only to allow the
// creation of multiple default_alloc instances.
// Node that containers built on different allocator instances have
// different types, limiting the utility of this approach.
#ifdef __SUNPRO_CC
// breaks if we make these template class members:
  enum {__ALIGN = 8};
  enum {__MAX_BYTES = 128};
  enum {__NFREELISTS = __MAX_BYTES/__ALIGN};
#endif

//第二级分配器的定义
//无”template型别参数“，第一个参数用于多线程环境，第二参数完全没派上用场
template <bool threads, int inst>
class __default_alloc_template {

private:
  // Really we should use static const int x = N
  // instead of enum { x = N }, but few compilers accept the former.
# ifndef __SUNPRO_CC
    enum {__ALIGN = 8};
    enum {__MAX_BYTES = 128};
    enum {__NFREELISTS = __MAX_BYTES/__ALIGN};
# endif
  //将bytes上调至8的倍数
  static size_t ROUND_UP(size_t bytes) {
        return (((bytes) + __ALIGN-1) & ~(__ALIGN - 1));
  }
__PRIVATE:
  //free-list
  union obj {
        union obj * free_list_link;
        char client_data[1];    /* The client sees this.        */
  };
private:
# ifdef __SUNPRO_CC
    static obj * __VOLATILE free_list[]; 
        // Specifying a size results in duplicate def for 4.1
# else
    //16个free-list
    static obj * __VOLATILE free_list[__NFREELISTS]; 
# endif
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

# ifdef __STL_SGI_THREADS
    static volatile unsigned long __node_allocator_lock;
    static void __lock(volatile unsigned long *); 
    static inline void __unlock(volatile unsigned long *);
# endif

# ifdef __STL_PTHREADS
    static pthread_mutex_t __node_allocator_lock;
# endif

# ifdef __STL_WIN32THREADS
    static CRITICAL_SECTION __node_allocator_lock;
    static bool __node_allocator_lock_initialized;

  public:
    __default_alloc_template() {
	// This assumes the first constructor is called before threads
	// are started.
        if (!__node_allocator_lock_initialized) {
            InitializeCriticalSection(&__node_allocator_lock);
            __node_allocator_lock_initialized = true;
        }
    }
  private:
# endif

    class lock {
        public:
            lock() { __NODE_ALLOCATOR_LOCK; }
            ~lock() { __NODE_ALLOCATOR_UNLOCK; }
    };
    friend class lock;

public:

  /* n must be > 0      */
  static void * allocate(size_t n)
  {
    obj * __VOLATILE * my_free_list;
    obj * __RESTRICT result;

    //大于128就调用第一级分配器
    if (n > (size_t) __MAX_BYTES) {
        return(malloc_alloc::allocate(n));
    }
    //寻找16个free-list中适当的一个
    my_free_list = free_list + FREELIST_INDEX(n);
    // Acquire the lock here with a constructor call.
    // This ensures that it is released in exit or during stack
    // unwinding.
#       ifndef _NOTHREADS
        /*REFERENCED*/
        lock lock_instance;
#       endif
    result = *my_free_list;
    if (result == 0) {
        //没找到可用的free-list，准备重新填充free-list
        void *r = refill(ROUND_UP(n));
        return r;
    }
    //调整free list
    *my_free_list = result -> free_list_link;
    return (result);
  };

  /* p may not be 0 */
  static void deallocate(void *p, size_t n)
  {
    obj *q = (obj *)p;
    obj * __VOLATILE * my_free_list;

    //大于128就调用第一级分配器
    if (n > (size_t) __MAX_BYTES) {
        malloc_alloc::deallocate(p, n);
        return;
    }
    //寻找对应的free-list
    my_free_list = free_list + FREELIST_INDEX(n);
    // acquire lock
#       ifndef _NOTHREADS
        /*REFERENCED*/
        lock lock_instance;
#       endif /* _NOTHREADS */
    //调整free-list，回收区块
    q -> free_list_link = *my_free_list;
    *my_free_list = q;
    // lock is released here
  }

  static void * reallocate(void *p, size_t old_sz, size_t new_sz);

} ;

typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS, 0> alloc;
typedef __default_alloc_template<false, 0> single_client_alloc;



// 假设size已经适当上调至8的倍数  
// 注意参数nobjs是pass by reference
template <bool threads, int inst>
char*
__default_alloc_template<threads, inst>::chunk_alloc(size_t size, int& nobjs)
{
    char * result;
    size_t total_bytes = size * nobjs;
    size_t bytes_left = end_free - start_free; //内存池剩余空间

    if (bytes_left >= total_bytes) {
        //内存池剩余空间完全满足需求量
        result = start_free;
        start_free += total_bytes;
        return(result);
    } else if (bytes_left >= size) {
        //内存池剩余空间不能完全满足需求量，但足够供应一个(含)以上的区块
        //那么能分配多少区块，就分配多少区块
        nobjs = bytes_left/size;    //可分配的区块数
        total_bytes = size * nobjs; //总共可分配的字节数
        result = start_free;
        start_free += total_bytes;
        return(result);
    } else {//内存池剩余空间连一个区块的大小都无法提供
        //计算需要从heap申请的空间数量，用以补充内存池
        size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
        // 试着让内存池中的残余零头还有利用价值
        if (bytes_left > 0) {
            //内存池中还有一些零头，先配给适当的free-list
            //首先寻找适当的free-list
            obj * __VOLATILE * my_free_list =
                        free_list + FREELIST_INDEX(bytes_left);
            //调整free-list，将内存池中的残余空间编入
            ((obj *)start_free) -> free_list_link = *my_free_list;
            *my_free_list = (obj *)start_free;
        }
        //调用malloc，分配heap空间，用来补充内存池
        start_free = (char *)malloc(bytes_to_get);
        if (0 == start_free) {
            //heap空间不足，malloc()失败
            int i;
            obj * __VOLATILE * my_free_list, *p;
            // 试着检视我们手上拥有的东西。这不会造成伤害。我们不打算尝试分配
            // 较小的区块，因为那在多进程机器上容易导致灾难
            // 以下搜寻适当的free-list
            // 所谓适当是指”尚有未用区块，且区块够大“的free-list
            for (i = size; i <= __MAX_BYTES; i += __ALIGN) {
                my_free_list = free_list + FREELIST_INDEX(i);
                p = *my_free_list;
                if (0 != p) {//free-list内尚有未用区块
                    //调整free-list以释出未用区块
                    *my_free_list = p -> free_list_link;
                    start_free = (char *)p;
                    end_free = start_free + i;
                    //递归调用自身，为了修正nobjs
                    return(chunk_alloc(size, nobjs));
                    //任何残余零头终将被编入适当的free-list中备用
                }
            }
	    end_free = 0;	// 山穷水尽，到处都没有内存可用
        //调用第一级分配器，看看out-of-memory机制能否尽点力
            start_free = (char *)malloc_alloc::allocate(bytes_to_get);
            // 可能会抛出异常，或者内存不足的情况获得改善
        }
        heap_size += bytes_to_get;
        end_free = start_free + bytes_to_get;
        //递归调用自身，为了修正nobjs
        return(chunk_alloc(size, nobjs));
    }
}


/* 返回一个大小为n的对象，并且有时候会为适当的free-list增加节点.*/
/* 假设n已经适当上调至8的倍数                               */
/* 需要获得分配锁                                          */
template <bool threads, int inst>
void* __default_alloc_template<threads, inst>::refill(size_t n)
{
    int nobjs = 20;
    //调用chunk_alloc()，尝试取得njobs个区块作为free-list的新节点
    //参数nobjs是pass by reference
    char * chunk = chunk_alloc(n, nobjs);
    obj * __VOLATILE * my_free_list;
    obj * result;
    obj * current_obj, * next_obj;
    int i;

    //如果只获得一个区块，这个区块就分配给调用者用，free-list无新节点
    if (1 == nobjs) return(chunk);
    //否则准备调整free-list，纳入新节点
    my_free_list = free_list + FREELIST_INDEX(n);

    /* 在chunk空间内建立free-list */
      result = (obj *)chunk;    //这一块准备返回给客户
      //以下引导free-list指向新分配的空间（取自内存池）
      *my_free_list = next_obj = (obj *)(chunk + n);
      //以下将free-list的各节点串接起来
      for (i = 1; ; i++) {//从1开始，因为第0个将返回给客户
        current_obj = next_obj;
        next_obj = (obj *)((char *)next_obj + n);
        if (nobjs - 1 == i) {
            current_obj -> free_list_link = 0;
            break;
        } else {
            current_obj -> free_list_link = next_obj;
        }
      }
    return(result);
}

template <bool threads, int inst>
void*
__default_alloc_template<threads, inst>::reallocate(void *p,
                                                    size_t old_sz,
                                                    size_t new_sz)
{
    void * result;
    size_t copy_sz;

    if (old_sz > (size_t) __MAX_BYTES && new_sz > (size_t) __MAX_BYTES) {
        return(realloc(p, new_sz));
    }
    if (ROUND_UP(old_sz) == ROUND_UP(new_sz)) return(p);
    result = allocate(new_sz);
    copy_sz = new_sz > old_sz? old_sz : new_sz;
    memcpy(result, p, copy_sz);
    deallocate(p, old_sz);
    return(result);
}

#ifdef __STL_PTHREADS
    template <bool threads, int inst>
    pthread_mutex_t
    __default_alloc_template<threads, inst>::__node_allocator_lock
        = PTHREAD_MUTEX_INITIALIZER;
#endif

#ifdef __STL_WIN32THREADS
    template <bool threads, int inst> CRITICAL_SECTION
    __default_alloc_template<threads, inst>::__node_allocator_lock;

    template <bool threads, int inst> bool
    __default_alloc_template<threads, inst>::__node_allocator_lock_initialized
	= false;
#endif

#ifdef __STL_SGI_THREADS
__STL_END_NAMESPACE
#include <mutex.h>
#include <time.h>
__STL_BEGIN_NAMESPACE
// Somewhat generic lock implementations.  We need only test-and-set
// and some way to sleep.  These should work with both SGI pthreads
// and sproc threads.  They may be useful on other systems.
template <bool threads, int inst>
volatile unsigned long
__default_alloc_template<threads, inst>::__node_allocator_lock = 0;

#if __mips < 3 || !(defined (_ABIN32) || defined(_ABI64)) || defined(__GNUC__)
#   define __test_and_set(l,v) test_and_set(l,v)
#endif

template <bool threads, int inst>
void 
__default_alloc_template<threads, inst>::__lock(volatile unsigned long *lock)
{
    const unsigned low_spin_max = 30;  // spin cycles if we suspect uniprocessor
    const unsigned high_spin_max = 1000; // spin cycles for multiprocessor
    static unsigned spin_max = low_spin_max;
    unsigned my_spin_max;
    static unsigned last_spins = 0;
    unsigned my_last_spins;
    static struct timespec ts = {0, 1000};
    unsigned junk;
#   define __ALLOC_PAUSE junk *= junk; junk *= junk; junk *= junk; junk *= junk
    int i;

    if (!__test_and_set((unsigned long *)lock, 1)) {
        return;
    }
    my_spin_max = spin_max;
    my_last_spins = last_spins;
    for (i = 0; i < my_spin_max; i++) {
        if (i < my_last_spins/2 || *lock) {
            __ALLOC_PAUSE;
            continue;
        }
        if (!__test_and_set((unsigned long *)lock, 1)) {
            // got it!
            // Spinning worked.  Thus we're probably not being scheduled
            // against the other process with which we were contending.
            // Thus it makes sense to spin longer the next time.
            last_spins = i;
            spin_max = high_spin_max;
            return;
        }
    }
    // We are probably being scheduled against the other process.  Sleep.
    spin_max = low_spin_max;
    for (;;) {
        if (!__test_and_set((unsigned long *)lock, 1)) {
            return;
        }
        nanosleep(&ts, 0);
    }
}

template <bool threads, int inst>
inline void
__default_alloc_template<threads, inst>::__unlock(volatile unsigned long *lock)
{
#   if defined(__GNUC__) && __mips >= 3
        asm("sync");
        *lock = 0;
#   elif __mips >= 3 && (defined (_ABIN32) || defined(_ABI64))
        __lock_release(lock);
#   else 
        *lock = 0;
        // This is not sufficient on many multiprocessors, since
        // writes to protected variables and the lock may be reordered.
#   endif
}
#endif

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::start_free = 0;

template <bool threads, int inst>
char *__default_alloc_template<threads, inst>::end_free = 0;

template <bool threads, int inst>
size_t __default_alloc_template<threads, inst>::heap_size = 0;

template <bool threads, int inst>
__default_alloc_template<threads, inst>::obj * __VOLATILE
__default_alloc_template<threads, inst> ::free_list[
# ifdef __SUNPRO_CC
    __NFREELISTS
# else
    __default_alloc_template<threads, inst>::__NFREELISTS
# endif
] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
// The 16 zeros are necessary to make version 4.1 of the SunPro
// compiler happy.  Otherwise it appears to allocate too little
// space for the array.

# ifdef __STL_WIN32THREADS
  // Create one to get critical section initialized.
  // We do this onece per file, but only the first constructor
  // does anything.
  static alloc __node_allocator_dummy_instance;
# endif

#endif /* ! __USE_MALLOC */

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1174
#endif

__STL_END_NAMESPACE

#undef __PRIVATE

#endif /* __SGI_STL_INTERNAL_ALLOC_H */

// Local Variables:
// mode:C++
// End:
