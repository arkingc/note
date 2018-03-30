class Solution
{
public:
  //Insert one char from stringstream
    void Insert(char ch)
    {
         if(positions[ch] == -1)
            positions[ch] = index;
         else
             positions[ch] = -2;
        index++;
    }
  //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        int minidx = index;
        char ch;
        for(int j = 0;j < 256;j++)
            if(positions[j] >= 0 && positions[j] < minidx){
                minidx = positions[j];
                ch = j;
            }
        if (minidx == index)
            ch = '#';
        return ch;
    }
    Solution(){
        index = 0;
        for(int i = 0;i < 256;i++)
            positions[i] = -1;
    }
private:
    int index;
    int positions[256];
};