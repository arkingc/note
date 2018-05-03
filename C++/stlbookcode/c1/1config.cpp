#include <iostream>
#include <stdio.h>
using namespace std;


void test(void)
{
#ifdef _PTHREADS
    cout<<"define __STL_PTHREADS"<<endl;
#endif

# if defined(__sgi) && !defined(__GNUC__)
    cout<<"__sgi begin"<<endl;
# if !defined(_BOOL)
        cout<<"__STL_NEED_BOOL"<<endl;
# endif
# if !defined(_TYPENAME_IS_KEYWORD)
         cout<<"__STL_NEED_TYPENAME"<<endl;
# endif
# ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
        cout<<"__STL_CLASS_PARTIAL_SPECIALIZATION"<<endl;
# endif
# ifdef _MEMBER_TEMPLATES
        cout<<"__STL_MEMBER_TEMPLATES"<<endl;
# endif
# if !defined(_EXPLICIT_IS_KEYWORD)
        cout<<"__STL_NEED_EXPLICIT"<<endl;
# endif
# ifdef __EXCEPTIONS
        cout<<"__STL_USE_EXCEPTIONS"<<endl;
# endif
# if (_COMPILER_VERSION >= 721) && defined(_NAMESPACES)
        cout<<"__STL_USE_NAMESPACES"<<endl;
# endif
# if !defined(_NOTHREADS) && !defined(__STL_PTHREADS)
        cout<<"__STL_SGI_THREADS"<<endl;
# endif
    cout<<"__sgi end"<<endl<<endl;
# endif

# ifdef __GNUC__
    cout<<"__GNUC__ begin"<<endl;
//# include <_G_config.h>
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8)
        cout<<"__STL_STATIC_TEMPLATE_MEMBER_BUG"<<endl;
        cout<<"__STL_NEED_TYPENAME"<<endl;
        cout<<"__STL_NEED_EXPLICIT"<<endl;
# else
        cout<<"__STL_CLASS_PARTIAL_SPECIALIZATION"<<endl;
        cout<<"__STL_FUNCTION_TMPL_PARTIAL_ORDER"<<endl;
        cout<<"__STL_EXPLICIT_FUNCTION_TMPL_ARGS"<<endl;
        cout<<"__STL_MEMBER_TEMPLATES"<<endl;
# endif
    /* glibc pre 2.0 is very buggy. We have to disable thread for it.
       It should be upgraded to glibc 2.0 or later. */
# if !defined(_NOTHREADS) && __GLIBC__ >= 2 && defined(_G_USING_THUNKS)
        cout<<"__STL_PTHREADS"<<endl;
# endif
# ifdef __EXCEPTIONS
        cout<<"__STL_USE_EXCEPTIONS"<<endl;
# endif
    cout<<"__GNUC__ end"<<endl<<endl;
# endif

# if defined(__SUNPRO_CC)
    cout<<"__SUNPRO_CC begin"<<endl;
    cout<<"__STL_NEED_BOOL"<<endl;
    cout<<"__STL_NEED_TYPENAME"<<endl;
    cout<<"__STL_NEED_EXPLICIT"<<endl;
    cout<<"__STL_USE_EXCEPTIONS"<<endl;
    cout<<"__SUNPRO_CC end"<<endl<<endl;
# endif

# if defined(__COMO__)
    cout<<"__COMO__ begin"<<endl;
    cout<<"__STL_MEMBER_TEMPLATES"<<endl;
    cout<<"__STL_CLASS_PARTIAL_SPECIALIZATION"<<endl;
    cout<<"__STL_USE_EXCEPTIONS"<<endl;
    cout<<"__STL_USE_NAMESPACES"<<endl;
    cout<<"__COMO__ end"<<endl<<endl;
# endif

# if defined(_MSC_VER)
cout<<"_MSC_VER begin"<<endl;
# if _MSC_VER > 1000
        cout<<"include "<<endl;
# else
        cout<<"__STL_NEED_BOOL"<<endl;
# endif
        cout<<"__STL_NO_DRAND48"<<endl;
        cout<<"__STL_NEED_TYPENAME"<<endl;
# if _MSC_VER < 1100
        cout<<"__STL_NEED_EXPLICIT"<<endl;
# endif
        cout<<"__STL_NON_TYPE_TMPL_PARAM_BUG"<<endl;
        cout<<"__SGI_STL_NO_ARROW_OPERATOR"<<endl;
# ifdef _CPPUNWIND
        cout<<"__STL_USE_EXCEPTIONS"<<endl;
# endif
# ifdef _MT
        cout<<"__STL_WIN32THREADS"<<endl;
# endif
    cout<<"_MSC_VER end"<<endl<<endl;
# endif

# if defined(__BORLANDC__)
    cout<<"__BORLANDC__ begin"<<endl;
    cout<<"__STL_NO_DRAND48"<<endl;
    cout<<"__STL_NEED_TYPENAME"<<endl;
    cout<<"__STL_LIMITED_DEFAULT_TEMPLATES"<<endl;
    cout<<"__SGI_STL_NO_ARROW_OPERATOR"<<endl;
    cout<<"__STL_NON_TYPE_TMPL_PARAM_BUG"<<endl;
# ifdef _CPPUNWIND
        cout<<"__STL_USE_EXCEPTIONS"<<endl;
# endif
# ifdef __MT__
        cout<<"__STL_WIN32THREADS"<<endl;
# endif
    cout<<"__BORLANDC__ end"<<endl<<endl;
# endif


# if defined(__STL_NEED_BOOL)
    cout<<"__STL_NEED_BOOL begin"<<endl;
    cout<<"typedef int bool;"<<endl;
    cout<<"define true 1"<<endl;
    cout<<"define false 0"<<endl;
    cout<<"__STL_NEED_BOOL end"<<endl<<endl;
# endif

# ifdef __STL_NEED_TYPENAME
    cout<<"define typename"<<endl;
# endif

# ifdef __STL_NEED_EXPLICIT
    cout<<"define explicit"<<endl;
# endif

# ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
    cout<<"__STL_NULL_TMPL_ARGS <>"<<endl;
# else
    cout<<"__STL_NULL_TMPL_ARGS"<<endl;
# endif

# ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
    cout<<"__STL_TEMPLATE_NULL template<>"<<endl;
# else
    cout<<"__STL_TEMPLATE_NULL"<<endl;
# endif

// __STL_NO_NAMESPACES is a hook so that users can disable namespaces
// without having to edit library headers.
# if defined(__STL_USE_NAMESPACES) && !defined(__STL_NO_NAMESPACES)
    cout<<"__STL_USE_NAMESPACES begin"<<endl;
    cout<<"__STD std"<<endl;
    cout<<"__STL_BEGIN_NAMESPACE namespace std {"<<endl;
    cout<<"__STL_END_NAMESPACE }"<<endl;
    cout<<"__STL_USE_NAMESPACE_FOR_RELOPS"<<endl;
    cout<<"__STL_BEGIN_RELOPS_NAMESPACE namespace std {"<<endl;
    cout<<"__STL_END_RELOPS_NAMESPACE }"<<endl;
    cout<<"__STD_RELOPS std"<<endl;
    cout<<"__STL_USE_NAMESPACES end"<<endl<<endl;
# else
    cout<<"! __STL_USE_NAMESPACES begin"<<endl;
    cout<<"__STD "<<endl;
    cout<<"__STL_BEGIN_NAMESPACE "<<endl;
    cout<<"__STL_END_NAMESPACE "<<endl;
    cout<<"__STL_USE_NAMESPACE_FOR_RELOPS"<<endl;
    cout<<"__STL_BEGIN_RELOPS_NAMESPACE "<<endl;
    cout<<"__STL_END_RELOPS_NAMESPACE "<<endl;
    cout<<"__STD_RELOPS "<<endl;
    cout<<"! __STL_USE_NAMESPACES end"<<endl<<endl;
# endif

# ifdef __STL_USE_EXCEPTIONS
    cout<<"__STL_USE_EXCEPTIONS begin"<<endl;
    cout<<"__STL_TRY try"<<endl;
    cout<<"__STL_CATCH_ALL catch(...)"<<endl;
    cout<<"__STL_RETHROW throw"<<endl;
    cout<<"__STL_NOTHROW throw()"<<endl;
    cout<<"__STL_UNWIND(action) catch(...) { action; throw; }"<<endl;
    cout<<"__STL_USE_EXCEPTIONS end"<<endl<<endl;
# else
    cout<<"! __STL_USE_EXCEPTIONS begin"<<endl;
    cout<<"__STL_TRY "<<endl;
    cout<<"__STL_CATCH_ALL if (false)"<<endl;
    cout<<"__STL_RETHROW "<<endl;
    cout<<"__STL_NOTHROW "<<endl;
    cout<<"__STL_UNWIND(action) "<<endl;
    cout<<"! __STL_USE_EXCEPTIONS end"<<endl<<endl;
# endif

#ifdef __STL_ASSERTIONS
# include <stdio.h>
    cout<<"__stl_assert(expr) \
    if (!(expr)) { fprintf(stderr, \"%s:%d STL assertion failure: %s\n\", \
             __FILE__, __LINE__, # expr); abort(); }"<<endl;
#else
    cout<<"__stl_assert(expr)"<<endl;
#endif
}

int main(void)
{
    /*************************************
    编译器：clang-800.0.42.1
    
    __GNUC__ begin
    __STL_CLASS_PARTIAL_SPECIALIZATION
    __STL_FUNCTION_TMPL_PARTIAL_ORDER
    __STL_EXPLICIT_FUNCTION_TMPL_ARGS
    __STL_MEMBER_TEMPLATES
    __STL_USE_EXCEPTIONS
    __GNUC__ end

    __STL_NULL_TMPL_ARGS
    __STL_TEMPLATE_NULL
    ! __STL_USE_NAMESPACES begin
    __STD
    __STL_BEGIN_NAMESPACE
    __STL_END_NAMESPACE
    __STL_USE_NAMESPACE_FOR_RELOPS
    __STL_BEGIN_RELOPS_NAMESPACE
    __STL_END_RELOPS_NAMESPACE
    __STD_RELOPS
    ! __STL_USE_NAMESPACES end

    ! __STL_USE_EXCEPTIONS begin
    __STL_TRY
    __STL_CATCH_ALL if (false)
    __STL_RETHROW
    __STL_NOTHROW
    __STL_UNWIND(action)
    ! __STL_USE_EXCEPTIONS end

    __stl_assert(expr)
    *************************************/

    test();

    return 0;
}