/*
 * '.':
 *     match[i,j] = match[i - 1,j - 1];
 * '*':
 *     match[i,j] = match[i,j - 2] || (str[i] == pattern[j - 1] && match[i-1,j]);
 * else:
 *     match[i,j] = match[i-1,j-1] && str[i] == pattern[j]
 */

class Solution {
public:
    bool match(char *str,char *pattern,int idx1,int idx2){
        if(idx2 < 0)
            return idx1 < 0;
        
        if(idx1 < 0){
            return idx2 >= 0 && pattern[idx2] == '*' && match(str,pattern,idx1,idx2 - 2);
        }
        
        if(pattern[idx2] == '*'){
            if(idx2 > 0){
                return ((str[idx1] == pattern[idx2 - 1] || pattern[idx2-1] == '.') && match(str,pattern,idx1-1,idx2)) || match(str,pattern,idx1,idx2-2);
            }
            return false;
        }
        else if(pattern[idx2] == '.'){
            return match(str,pattern,idx1 - 1,idx2-1);
        }
        else{
            return str[idx1] == pattern[idx2] && match(str,pattern,idx1-1,idx2-1);
        }
    }
    bool match(char* str, char* pattern)
    {
        if(!str || !pattern)
            return false;
        
        int sz1 = 0,sz2 = 0;
        while(str[sz1] != '\0')
            sz1++;
        while(pattern[sz2] != '\0')
            sz2++;
        
        return match(str,pattern,sz1 - 1,sz2 - 1);
    }
};