```c++
#include <cassert>

//字符串长度计算
int strlen(const char *str)
{
    assert(str);

    int len = 0;
    while(*str++)   len++;
    return  len;
}

//字符串比较
int strcmp(const char *str1,const char *str2)
{
    assert(str1 && str2);

    int ret = 0;
    while(!(ret = *(unsigned char *)str1 - *(unsigned char *)str2) && *str1){
        str1++;
        str2++;
    }

    if(ret < 0) ret = -1;
    else if(ret > 0) ret = 1;
    return ret;
}

//字符串拼接
char* strcat(char *strDest,const char *strSrc)
{
    assert(strDest && strSrc);

    char *p = strDest;
    while(*p) p++;

    while(*p++ = *strSrc++);
    return strDest;
}

//字符串拷贝
char* strcpy(char *strDest,const char *strSrc)
{
    assert(strDest && strSrc);

    char *p;
    while(*p++ = *strSrc++);
    return strDest;
}
```