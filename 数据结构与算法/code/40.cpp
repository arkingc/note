class Solution {
public:
    int partition(vector<int> &input,int l,int r){
        int i = l - 1,tp;
        int pivot = input[r];
        for(int j = l;j < r;j++){
            if(input[j] < pivot){
                tp = input[++i];
                input[i] = input[j];
                input[j] = tp;
            }
        }
        
        tp = input[++i];
        input[i] = pivot;
        input[r] = tp;
        
        return i;
    }
    
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
      
        if(input.size() < k){
            return res;
        }
        
        if(k <= 0 || input.size() < k)
            return res;
        
        int index = partition(input,0,input.size() - 1);
        while(index != k - 1){
            if(index > k - 1){
                index = partition(input,0,index - 1);
            }
            else{
                index = partition(input,index + 1,input.size() - 1);
            }
        }
        
        for(int i = 0;i < k;i++){
            res.push_back(input[i]);
        }
        
        return res;
    }
};