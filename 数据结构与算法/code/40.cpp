/*
 *   1）基于partition函数的方法（不适合海量数据）；
 *   2）使用容器(最大堆)存储最小的k个数，遍历数组，当有更小的数时替换掉原容器中最大的
 *     （适合处理海量数据，数组不能一次载入内存）​
 */
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