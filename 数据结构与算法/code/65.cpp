/*
 * 两数异或，会得到忽略所有进位的结果，然后两数位与结果左移1位，得到所有进位组成的数字，再对这两个结果重复上述步骤，直至没有进位；
 */

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