char g_StrCombine1[2 * 10 + 1];
char g_StrCombine2[2 * 10 + 1];

int compare(const void* strNumber1,const void* strNumber2){
    //如果转换改成(const char*)会得到错误的结果
    strcpy(g_StrCombine1,*(const char**)strNumber1);
    strcat(g_StrCombine1,*(const char**)strNumber2);

    strcpy(g_StrCombine2,*(const char**)strNumber2);
    strcat(g_StrCombine2,*(const char**)strNumber1);

    return strcmp(g_StrCombine1,g_StrCombine2);
}

class Solution {
public:
    string PrintMinNumber(vector<int> numbers) {
        if(numbers.size() == 0)
            return "";
        
        int sz = numbers.size();
        char **nbs = new char *[sz];
        for(int i = 0;i < sz;i++){
            nbs[i] = new char[11];
            sprintf(nbs[i],"%d",numbers[i]);
        }
        
        string res = "";
        qsort(nbs,sz,sizeof(char*),compare);
        for(int i = 0;i < sz;i++)
            res += nbs[i];
        
        for(int i = 0;i < sz;i++){
            delete [] nbs[i];
        }
        delete [] nbs;
        
        return res;
    }
};