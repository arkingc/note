/*
 * 1)循环n次，每次乘以x，时间复杂度：O(n)
 * 2)使用一个变量m表示指数，如果m*2<n，则将结果平方，指数增长，时间复杂度：O(logn)
 * 要考虑exponent=INT_MIN时，乘以-1会溢出，所以用long long保存指数
 */

class Solution {
public:
    double Power(double base, int exponent) {
        bool b = exponent < 0;
        
        if(base == 0)  return 0;
        if(exponent == 0)  return 1;
        
        //需要使用一个long long类型的变量，因为当n为INT_MIN时，和-1乘会溢出
        long long nl = exponent < 0 ? (long long)exponent * -1 : exponent;
        double ret = 1.0;
        
        while(nl){
            long long m = 1;//m必须也是long long,因为当m = INT_MAX/2+1时，计算m*2会溢出
            double tp = base;
            while(2 * m <= nl){
                tp *= tp;
                m *= 2;
            }
            nl = nl - m;
            ret *= tp;
        }
        
        ret = b ? 1 / ret : ret;
        return ret;
    }
};