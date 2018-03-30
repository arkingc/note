class Solution {
public:
    int GetNumberOfK(vector<int> data ,int k) {
        int l = GetFirstK(data,k);
        int r = GetLastK(data,k);
        
        if(l >= 0 && r >= 0)
            return r - l + 1;
        return 0;
    }
    
    int GetFirstK(vector<int> data,int k){
        if(data.size() == 0)
            return -1;
        
        int sz = data.size();
        int l = 0,r = sz - 1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(data[mid] > k)
                r = mid - 1;
            else if(data[mid] < k)
                l = mid + 1;
            else{
                if(mid == 0 || data[mid - 1] != k) 
                    return mid;
                else 
                    r = mid - 1;
            }
        }
        
        return -1;
    }
    
    int GetLastK(vector<int> data,int k){
        if(data.size() == 0)
            return -1;
        
        int sz = data.size();
        int l = 0,r = sz - 1;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(data[mid] > k)
                r = mid - 1;
            else if(data[mid] < k)
                l = mid + 1;
            else{
                if(mid == sz - 1 || data[mid + 1] != k)
                    return mid;
                else
                    l = mid + 1;
            }
        }
        
        return -1;
    }
};