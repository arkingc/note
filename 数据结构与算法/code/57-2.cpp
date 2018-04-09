/*
 * small初始化为1，big初始化为2。
 * 如果从small到big的序列的和大于s,则从序列中去掉较小的值，也就是增大small的值。
 * 如果从small到big的序列和小于s，则增大big，让序列包含更多的数字。
 * 如果正好等于s，则递增big，继续处理。
 * 因为至少含2个数字，一直增加small到(1+s)/2；​​
 */

class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        int small = 1,big = 2,s = 3;
        vector<vector<int> > res;
        
        while(small <= sum/2){
            if(s < sum){
                s += ++big;
            }
            else if(s > sum){
                s -= small++;
            }
            else{
                vector<int> seq;
                for(int i = small;i <= big;i++)
                    seq.push_back(i);
                res.push_back(seq);
                s -= small++;
            }
        }
        
        return res;
    }
};