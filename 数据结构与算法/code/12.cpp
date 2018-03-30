class Solution {
public:
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        if(!matrix || !str || rows == 0 || cols == 0)
            return false;
        
        int length = 0;
        char *p = matrix;
        while(*p != '\0'){
            length++;
            p++;
        }
        
        if(rows * cols != length)
            return false;
        
        bool *flag = new bool[rows * cols];
        for(int i = 0;i < rows * cols;i++){
            flag[i] = false;
        }
        
        for(int row = 0;row < rows;row++){
            for(int col = 0;col < cols;col++){
                if(hasPathCore(matrix,rows,cols,str,row,col,flag))
                    return true;
            }
        }
        
        return false;
    }

    bool hasPathCore(char* matrix,const int &rows,const int &cols,char* str,int row,int col,bool *flag){
        if(*str == '\0')
            return true;
        
        if(row < 0 || row >= rows || col < 0 || col >= cols || flag[row * cols + col] == true || matrix[row * cols + col] != *str)
            return false;
        
        flag[row * cols + col] = true;
        bool res = hasPathCore(matrix,rows,cols,str + 1,row - 1,col,flag) || hasPathCore(matrix,rows,cols,str + 1,row + 1,col,flag)
            || hasPathCore(matrix,rows,cols,str + 1,row,col - 1,flag) || hasPathCore(matrix,rows,cols,str + 1,row , col + 1,flag);
        
        if(!res)
            flag[row * cols + col] = false;
        return res;
    }
};