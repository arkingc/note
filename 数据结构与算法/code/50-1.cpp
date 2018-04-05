/*
 * 1）从头遍历每个字符，对于任意字符，遍历剩余字符看是否重复出现（O(n^2)）；
 * 2）用一个辅助数组，下标为字符，值为字符出现次数，第一次遍历时统计每个字符的出现次数，第二次遍历找到第一个只出现一次的字符（O(n)）；
 */

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