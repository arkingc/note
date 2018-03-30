class Solution {
public:
    //参数length表示str开始的可用内存空间
	void replaceSpace(char *str,int length) {
        if(length <= 0)
            return ;
        
        int length1 = 0,blankNumber = 0,i = 0;
        while(str[i] != '\0'){
            if(str[i] == ' ')
                blankNumber++;
            length1++;
            i++;
        }
            
        int length2 = length1 + 2 * blankNumber;
        if(length2 >= length)
            return;
        
        int curr = length2 - 1;
        for(int i = length1 - 1;i >= 0;i--){
            if(str[i] == ' '){
                str[curr--] = '0';
                str[curr--] = '2';
                str[curr--] = '%';
            }
            else
                str[curr--] = str[i];
        }
        str[length2] = '\0';
	}
};