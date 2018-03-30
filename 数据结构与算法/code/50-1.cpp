class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        int positions[256];
        
        for(int i = 0;i < 256;i++){
            positions[i] = -1;
        }
        
        int sz = str.size();
        for(int i = 0;i < sz;i++){
            if(positions[str[i]] == -1)
                positions[str[i]] = i;
            else
                positions[str[i]] = -2;
        }
        
        int minidx = sz - 1;
        for(int j = 0;j < 256;j++)
            if(positions[j] >= 0 && positions[j] < minidx)
                minidx = positions[j];
        return minidx;
    }
};