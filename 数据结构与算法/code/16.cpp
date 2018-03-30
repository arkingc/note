class Solution {
public:
    double Power(double base, int exponent) {
        bool negativeExp = (exponent < 0);
        
        if(base == 0)
            return 0;
        if(exponent == 0)
            return 1;
        
        if(exponent < 0)
            exponent *= -1;
        
        double res = 1;
        while(exponent--){
            res *= base;
        }
        
        if(negativeExp)
            return 1/res;
        return res;
    }
};