/*
 * 可以先考虑如果只有1个数字出现1次，其余都2次，怎么找:
 *   对所有数字异或，由于异或满足结合律交换律，结果就是所要查找的数字；
 * 对于存在2个数字出现1次的数字:
 *   所有数字异或结果为这两个数字的异或值，如果能将数组分为2部分，每个数字属于其中一部分，则能求出这两个数字。
 *   可以找到这两个数字异或结果中第一个为1的位，根据该位将数组分成2个数组；
 */

class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        int num1xornum2 = 0;
        int sz = data.size();
        
        for(int i = 0;i < sz;i++)
            num1xornum2 ^= data[i];
        
        int idx = 0;
        while(((num1xornum2 & 1) == 0) && (idx < 32)){
            idx++;
            num1xornum2 = num1xornum2 >> 1;
        }
        
        *num1 = 0,*num2 = 0;
        for(int i = 0;i < sz;i++){
            if(isBit(data[i],idx))
                *num1 ^= data[i];
            else
                *num2 ^= data[i];
        } 
    }
    
    bool isBit(int num,int idx){
        while(idx){
            num = num >> 1;
            idx--;
        }
        return (num & 1);
    }
    
    bool checknum(vector<int> &data,int num1,int num2){
        int count1 = 0,count2 = 0,sz = data.size();
        for(int i = 0;i < sz;i++){
            if(data[i] == num1)
                count1++;
            if(data[i] == num2)
                count2++;
        }
        
        return (count1 == 1) && (count2 == 1);
    }
};