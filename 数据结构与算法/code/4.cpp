/*
 * 选取右上角或左下角的元素，以左下角为例：
 * 1）如果左下角元素大于查找元素，则删除所在行；
 * 2）如果左上角元素小于查找元素，则删除所在列；
 */

class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int rows = array.size();
        int columns = array[0].size();
         
        int r = rows - 1,c = 0;
        while(r >= 0 && c < columns){
            if(array[r][c] < target)
                c++;
            else if(array[r][c] > target)
                r--;
            else
                return true;
        }
         
        return false;
    }
};