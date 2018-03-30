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