class Solution {
public:
    string ReverseSentence(string str) {
        if(str.size() < 2)
            return str;
         
        int sz = str.size();
        Reverse(str,0,sz - 1);
         
        int firstCharIdx = 0;
        for(int i = 0;i < sz;i++){
            if(str[i] == ' '){
                if(str[firstCharIdx] == ' ')
                    firstCharIdx++;
                else{
                    Reverse(str,firstCharIdx,i - 1);
                    firstCharIdx = i + 1;
                }
            }
        }
         
        if(str[sz - 1] != ' ')
            Reverse(str,firstCharIdx,sz - 1);
         
        return str;
    }
     
    void Reverse(string &str,int l,int r){
        if(l < 0 || r >= str.size())
            return;
         
        while(l < r){
            char c = str[r];
            str[r] = str[l];
            str[l] = c;
            l++;
            r--;
        }
    }
};
