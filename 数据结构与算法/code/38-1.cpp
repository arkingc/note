class Solution {
public:
    vector<string> Permutation(string str) {
        vector<string> res;
        if(str.size() == 0)
            return res;
        
        Permutation(str,0,res);
        sort(res.begin(),res.end());
        return res;
    }
    
    void Permutation(string &s,int idx,vector<string> &res){
        int sz = s.size();
        if(idx == (sz - 1)){
            res.push_back(s);
            return;
        }
        
        set<char> swaped;
        for(int i = idx;i < sz;i++){
            char c = s[i];
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