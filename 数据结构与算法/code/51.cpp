/*
 * 1）遍历每个元素，在这个元素的后面剩余元素中查找比该元素小的元素，每找到一个组成一个逆序对；（O(n^2)）
 * 2）基于归并排序的方法；（O(nlogn)）
 */

class Solution {
public:
    int InversePairs(vector<int> data) {
       if(data.size() < 2)
           return 0;
        
        vector<int> tp = data;
        int count = 0,sz = data.size();
        InversePairs(data,tp,count,0,sz - 1);
        
        return count;
    }
    
    void InversePairs(vector<int> &data,vector<int> &tp,int &count,int l,int r){
        if(l >= r)
            return;
        
        int mid = (l + r)/2;
        InversePairs(data,tp,count,l,mid);
        InversePairs(data,tp,count,mid + 1,r);
        
        //归并
        int idx1 = mid,idx2 = r,curr = r;
        while(idx1 >= l && idx2 >= mid + 1){
            if(data[idx1] > data[idx2]){//有逆序对
                count = (idx2 - mid + count) % 1000000007;
                tp[curr--] = data[idx1--];
            }
            else{
                tp[curr--] = data[idx2--];
            }
        }
        while(idx1 >= l)
            tp[curr--] = data[idx1--];
        while(idx2 >= mid + 1)
            tp[curr--] = data[idx2--];
        
        for(int i = l;i <= r;i++)
            data[i] = tp[i];
    }
};