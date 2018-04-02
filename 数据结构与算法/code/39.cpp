/*
 * 1）基于partition函数的方法；
​ * 2）该数字出现的次数超过其它数字出现的次数之和（因此，考虑使用2个变量，一个保存数字，一个保存次数。
 *    当遍历到下一个数字时，如果下一数字和之前保存的数字相同，则次数加1，
 *    如果下一数字和之前保存的数字不同，则次数减1。如果次数为0，则需保存下一个数字，并把次数设为1,
 *    最后一次把次数设为1时对应的数字就是结果）​；
 */

class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if(numbers.size() == 0)
            return 0;
        
        int count = 0;
        int res = numbers[0];
        for(int e : numbers){
            if(e == res)
                count++;
            else{
                if(count == 0)
                    res = e;
                else
                    count--;
            }
        }
        
        count = 0;
        for(int i = 0;i < numbers.size();i++){
            if(numbers[i] == res)
                count++;
        }
        if(count * 2 <= numbers.size())
            return 0;
        return res;
    }
};