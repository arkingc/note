/*
 * 1）先排序（时:O(nlogn)  空:O(1)）​
 * 2）哈希表（时:O(n)  空:O(n)）​
 * 由于数组内中的数字范围是[0,n-1]，因此还有方法3）：
 * 3）扫描，如果位置i的数字m不等于i，与位置m的数字比较、交换​（时:O(n)  空:O(1)）
 *
 * 可以扩展为海量数据的问题，n很大，范围都在[0,n-1]：
 *  1）求任意重复出现的数字
 *  2）求所有重复出现的数字
 * 都可以使用位图
 */

class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        if(length <= 2)
            return false;
        for(int i = 0;i < length;i++){
            while(numbers[i] != i){
                int m = numbers[i];
                if(m < 0 || m >= length)
                    return false;
                if(m == numbers[m]){
                    *duplication = m;
                    return true;
                }
                numbers[i] = numbers[m];
                numbers[m] = m;
            }
        }
        
        return false;
    }
};