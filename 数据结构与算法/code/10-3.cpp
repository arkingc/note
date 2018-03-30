class Solution {
public:
    int jumpFloorII(int number) {
        if(number <= 0)
            return 0;
        
        if(number == 1)
            return 1;
        
        int res = 1;
        for(int i = 2;i <= number;i++){
            res *= 2;
        }
        
        return res;
    }
};