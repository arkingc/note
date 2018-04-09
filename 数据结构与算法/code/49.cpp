/*
 * 丑数的判断：如果能被2整除，就连续除以2。如果能被3整除，就连续除以3。如果能被5整除，就连续除以5。如果最后得到的是1，这个数就是丑数，否则不是；
 *
 * 1）从1开始逐个判断（不是丑数的数也会进行判断，有多余时间开销）
 * 2）创建数组保存已经找到的数组（空间换时间，一个丑数应该是另一个丑数乘以2，3或5的结果）​​​​​
 */

class Solution {
public:
    int minInTree(const int &a,const int &b,const int &c){
        if(a < b)
            return a < c ? a : c;
        else
            return b < c ? b : c;
    }
    int GetUglyNumber_Solution(int index) {
        if(index <= 0)//如果下标非法，返回0
            return 0;
        vector<int> uglyNumberArr;
        uglyNumberArr.push_back(1);
        
        int idx2 = 0,idx3 = 0,idx5 = 0,curr = 0;
        while(curr != index - 1){
            while(uglyNumberArr[idx2] * 2 <= uglyNumberArr[curr]) {idx2++;}
            while(uglyNumberArr[idx3] * 3 <= uglyNumberArr[curr]) {idx3++;}
            while(uglyNumberArr[idx5] * 5 <= uglyNumberArr[curr]) {idx5++;}
            
            uglyNumberArr.push_back(minInTree(uglyNumberArr[idx2] * 2,uglyNumberArr[idx3] * 3,uglyNumberArr[idx5] * 5));
            curr++;
        }
        
        return uglyNumberArr[curr];
    }
};