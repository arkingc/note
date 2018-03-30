class Solution {
public:
    vector<vector<int> > FindContinuousSequence(int sum) {
        int small = 1,big = 2,s = 3;
        vector<vector<int> > res;
        
        while(small <= sum/2){
            if(s < sum){
                s += ++big;
            }
            else if(s > sum){
                s -= small++;
            }
            else{
                vector<int> seq;
                for(int i = small;i <= big;i++)
                    seq.push_back(i);
                res.push_back(seq);
                s -= small++;
            }
        }
        
        return res;
    }
};