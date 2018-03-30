class Solution {
public:
    int movingCount(int threshold, int rows, int cols)
    {
        if(rows == 0 || cols == 0 || threshold < 0)
            return 0;
        
        bool *flags = new bool[rows * cols];
        for(int i = 0;i < rows * cols;i++){
            flags[i] = false;
        }
        
        int count = 0;
        movingCount(threshold,rows,cols,0,0,count,flags);
        
        delete flags;
        return count;
    }
    
    void movingCount(int threshold,int rows,int cols,int row,int col,int &count,bool* flags){
        if(row < 0 || row >= rows || col < 0 || col >= cols || flags[row * cols + col])
            return;
        
        if(contain(threshold,row,col)){
            count++;
            flags[row * cols + col] = true;
        }
        else
            return;
        
        movingCount(threshold,rows,cols,row - 1,col,count,flags);//上
        movingCount(threshold,rows,cols,row + 1,col,count,flags);//下
        movingCount(threshold,rows,cols,row,col - 1,count,flags);//左
        movingCount(threshold,rows,cols,row,col + 1,count,flags);//右
    }
    
private:
    bool contain(const int &threshold,int row,int col){
        int bitSum = 0;
        while(row){
            bitSum += row % 10;
            row = row / 10;
        } 
        
        while(col){
            bitSum += col % 10;
            col = col / 10;
        }
        
        return bitSum <= threshold;
    }
};