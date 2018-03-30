class Solution {
public:
    /*
     * 剑指offer中的题没有限制“必须保证原有顺序”
     * 如果要保证顺序，在i后面的j位置找到一个奇数时，需要把[i,...,j-1]的元素往后移动，然后把j交换到i位置，这样复杂度为O(n^2)
     * 则使用插入排序编码更简洁，如果要实现O(n)时间复杂度，必须使用一个辅助数组（空间换时间）
     * 总的来说，限定了“必须保证原有顺序”，使得题目的整个解法和不限定时，可以很不一样
     */
    void reOrderArray(vector<int> &array) {
        vector<int> tp = array;
        int oddcount = 0;
        for(int i : tp)
            if (i % 2 == 1)
                oddcount++;
        
        int m = 0,n = oddcount;
        for(int i : tp){
            if(i % 2 == 1)
                array[m++] = i;
            else
                array[n++] = i;
        }
    }
};