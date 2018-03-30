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