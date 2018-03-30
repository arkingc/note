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