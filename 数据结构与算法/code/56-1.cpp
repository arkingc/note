class Solution {
public:
    void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
        int num1xornum2 = 0;
        int sz = data.size();
        
        for(int i = 0;i < sz;i++)
            num1xornum2 ^= data[i];
        
        int idx = 0;
        while(((num1xornum2 & 1) == 0) && (idx < 32)){
            idx++;
            num1xornum2 = num1xornum2 >> 1;
        }
        
        *num1 = 0,*num2 = 0;
        for(int i = 0;i < sz;i++){
            if(isBit(data[i],idx))
                *num1 ^= data[i];
            else
                *num2 ^= data[i];
        } 
    }
    
    bool isBit(int num,int idx){
        while(idx){
            num = num >> 1;
            idx--;
        }
        return (num & 1);
    }
    
    bool checknum(vector<int> &data,int num1,int num2){
        int count1 = 0,count2 = 0,sz = data.size();
        for(int i = 0;i < sz;i++){
            if(data[i] == num1)
                count1++;
            if(data[i] == num2)
                count2++;
        }
        
        return (count1 == 1) && (count2 == 1);
    }
};