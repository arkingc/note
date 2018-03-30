class Solution {
public:
    int StrToInt(string str) {
        bool negative = false;
        
        int sz = str.size();
        if(sz == 0)
            return 0;
        
        int bg = 0;
        long long res = 0;
        if(str[0] == '-'){
            negative = true;
            bg++;
        }
        else if(str[0] == '+'){
            bg++;
        }
        if(sz == 1 && bg == 1)//只有正负号
            return 0;
        
        for(int i = bg;i < sz;i++){
            if(str[i] >= '0' && str[i] <= '9'){
                res = res * 10 + (str[i] - '0');
                if(!negative && res > 0x7FFFFFFF)//溢出
                    return 0;
                else if(negative && res > 0xFFFFFFFF)
                    return 0;
            }
            else
                return 0;
        }
        
        if(negative)
            res = -1 * res;
        
        return static_cast<int>(res);
    }
};