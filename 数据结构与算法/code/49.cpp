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