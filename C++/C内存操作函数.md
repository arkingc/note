```c++
//实际上是memmove，实际的memcpy是不考虑重叠的
void* memcpy(void *dst,const void *src,size_t size)
{
    if(dst == NULL || src == NULL){
        return NULL;
    }

    void *res = dst;//保留原指针
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
            *dst++ = *src++;
        }
    }

    return res;
}
```
