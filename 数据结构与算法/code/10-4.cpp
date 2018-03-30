class Solution {
public:
    int rectCover(int number) {
        if(number <= 0)
            return 0;
        if(number == 1)
            return 1;
        
        int res;
        int num1 = 1,num2 = 1;
        for(int i = 2;i <= number;i++){
            res = num1 + num2;
            num1 = num2;
            num2 = res;
        }
        
        return res;
    }
};