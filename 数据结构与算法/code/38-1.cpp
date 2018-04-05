/*
 * 1）求所有可能出现在第一个位置的字符，即把第一个字符和后面所有的字符交换；
 * 2）固定第一个字符，求后面所有字符的排列； 
 */

class Solution {
public:
    vector<string> Permutation(string str) {
        vector<string> res;
        if(str.size() == 0)
            return res;
        
        Permutation(str,0,res);
        //为了按字典序输出，需要排序
        sort(res.begin(),res.end());
        return res;
    }
    
    void Permutation(string &s,int idx,vector<string> &res){
        int sz = s.size();
        if(idx == (sz - 1)){
            res.push_back(s);
            return;
        }
        
        set<char> swaped;//为了处理相同的字符
        for(int i = idx;i < sz;i++){
            char c = s[i];
            //说明遇到了相同的字符
            if(swaped.find(c) != swaped.end()){
                continue;
            }
            swaped.insert(c);
            s[i] = s[idx];
            s[idx] = c;
            
            Permutation(s,idx+1,res);
            
            s[idx] = s[i];
            s[i] = c;
        }
    }
};