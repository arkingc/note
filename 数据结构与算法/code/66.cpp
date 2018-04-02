/*
 * ​可以将Bi的乘积分为两部分，左边为A[0]*A[1]*...*A[i-1]，右边为A[i+1]，A[i+2]...A[n-1]。
 * 可以先按自上而下为每个B[i]获得左边部分的乘积，然后自下而上获得右边部分的乘积​
 */

class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        vector<int> B;
        if(A.size() < 2)
            return B;
        
        int value = 1;
        B.push_back(1);
        for(int i = 1;i < A.size();i++){
            B.push_back(B.back() * A[i - 1]);
        }
        
        int tp = 1;
        for(int j = A.size() - 2;j >= 0;j--){
            tp = tp * A[j+1];
            B[j] *= tp;
        }
        
        return B;
    }
};