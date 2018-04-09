/*
 * 1)如下
 * 2)构造函数
 */

class Solution {
public:
    int Sum_Solution(int n) {
        int ret = n;
        ret && (ret = n + Sum_Solution(n - 1));
        return ret;
    }
};