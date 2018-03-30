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