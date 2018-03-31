/*
 *  假设总的放法为F(M)
 *  1）如果第一个竖着放，则需要求F(M-1)
 *  2）如果第一个横着放，那么这个矩形下面也必须横着放，需要求F(M-2)
 *  故 F(M) = F(M-1) + F(M-2)，该方程是一个斐波那契数列方程
 */

class Solution {
public:
    int rectCover(int number) {
        if(number <= 0)
            return 0;
        if(number == 1)
            return 1;
        
        /*
         * 使用num1和num2存储F(M-1)和F(M-2)，自底向上计算
         */
        int res;
        int num1 = 1,num2 = 1;
        for(int i = 2;i <= number;i++){
            res = num1 + num2;  //求出F(M)
            num1 = num2;        //使用F(M-1)更新F(M-2)
            num2 = res;         //使用F(M)更新F(M-1)
        }
        
        return res;
    }
};