class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size() == 0)
            return 0;
        if(rotateArray.size() == 1)
            return rotateArray[0];
        
        int sz = rotateArray.size();
        int l = 0,r = sz - 1;
        //如果没有旋转，不会进入循环，这样初始化会直接返回最左边元素
        int mid = l;
        while(rotateArray[r] <= rotateArray[l]){
            if(r - l == 1){
                mid = r;
                break;
            }
            mid = (l + r) >> 1;
            //如果首尾元素以及中间元素相等，那么没有办法判断中间元素到底是在左半部分还是右半部分，这时只能用顺序查找
            if(rotateArray[l] == rotateArray[r] && rotateArray[l] == rotateArray[mid]){
                int min = rotateArray[0];
                for(int i = 1;i < sz;i++){
                    if(rotateArray[i] < min) 
                        min = rotateArray[i];
                }
                return min;
            }
            if(rotateArray[mid] >= rotateArray[l])
                l = mid;
            else if(rotateArray[mid] <= rotateArray[r])
                r = mid;
        }
        return rotateArray[mid];
    }
};