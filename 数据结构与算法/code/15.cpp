/*
 * 1）常规解法：首先把n和1做与运算，判断n的最低位是不是为1。接着把1左移一位得到2，再和n做与运算...（循环次数等于整数二进制的位数。unsigned int flag = 1）;
 * 2）优化解法：一个整数减去1之后再和原来的整数做位与运算，得到的结果相当于把整数二进制表示中最右边的1变成0；（有多少个1就循环多少次）
 */

class Solution {
public:
     int  NumberOf1(int n) {
         int count = 0;
         
         while(n){
            n = (n - 1) & n;
            count++;
         }
         
         return count;
     }
};