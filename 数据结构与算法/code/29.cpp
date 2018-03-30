class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> res;
        if(matrix.size() == 0 || matrix[0].size() == 0)
            return res;
        
        int rows = matrix.size();
        int columns = matrix[0].size();
        
        int i = 0;
        while( (i * 2) < rows && (i * 2) < columns){
            int endX = columns - 1 - i;
            int endY = rows - 1 - i;
            for(int idx = i;idx <= endX;idx++){
                res.push_back(matrix[i][idx]);
            }
            
            if(i < endY){
                for(int idx = i + 1;idx <= endY;idx++){
                    res.push_back(matrix[idx][endX]);
                }
            }
            
            if(i < endX && i < endY)
                for(int idx = endX - 1;idx >= i;idx--){
                    res.push_back(matrix[endY][idx]);
                }
            
            if(i < endX && i < endY - 1)
                for(int idx = endY - 1;idx > i;idx--){
                    res.push_back(matrix[idx][i]);
                }
            
            i++;
        }
        
        return res;
    }
};