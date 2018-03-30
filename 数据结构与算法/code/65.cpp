class Solution {
public:
    int Add(int num1, int num2)
    {
        int res = num1 ^ num2;
        int jw = (num1 & num2) << 1;
        
        int tp;
        while(jw){
            tp = res;
            res = res ^ jw;
            jw = (tp & jw) << 1;
        }
        
        return res;
    }
};