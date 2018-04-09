/*
 * 首尾两个下标，向中间靠拢，如果和小于s，则移动首下标，大于s，则移动尾下标；
 */

class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        vector<int> res;
        if(array.size() < 2)
            return res;
        
        int idx1,idx2,min;
        bool first = true;
        int l = 0,r = array.size() - 1;
        while(l < r){
            if(array[l] + array[r] == sum){
                if(first){
                    min = array[l] * array[r];
                    idx1 = l,idx2 = r;
                    first = false;
                }
                else{
                    if (min > array[l] * array[r]){
                        min = array[l] * array[r];
                        idx1 = l,idx2 = r;
                    }
                }
                l++;//r--应该也可以
            }
            else if(array[l] + array[r] < sum){
                l++;
            }
            else{//大于sum
                r--;
            }
        }
        
        if(first)
            return res;
        res.push_back(array[idx1]);
        res.push_back(array[idx2]);
        return res;
    }
};