/*
 * 动态规划:
 *  令sum[i]表示所有以位置i的元素结尾的连续子数组的最大和
 *  则状态转移方程如下:
 *   1) sum[i+1] = array[i + 1] (sum[i] <= 0)
 *   2) sum[i+1] = sum[i] + array[i + 1] (sum[i] > 0)
 *  那么连续子数组的最大和，就是max{sum[0],sum[1],...,sum[n-1]} 
 */

class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        if(array.size() == 0)
            return 0;

        int sum = array[0],res = array[0];
        int sz = array.size();
        for(int i = 1;i < sz;i++){
            if(sum > 0)
                sum += array[i];
            else
                sum = array[i];
            if(sum > res)
                res = sum;
        }
        
        return res;
    }
};