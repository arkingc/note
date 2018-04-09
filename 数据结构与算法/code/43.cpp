/*
 * 每次截去最高位作为划分，递归处理；
 * 如：n=21345，分成2段
 * 1）1~1345；
 * 2）1346~21345；​
 * 第一部分的次数递归处理，对于第二部分，当1在最高位时，因为范围包括了以1位最高位的所有5位数（10000~19999），所有总共出现10^(位数-1)次​，
 * 如果是到11345，则不包括所有以1位最高位的5位数，因此只出现1345+1次。当1在其余4位时，​出现2(最高位数字)*(10^(位数-2))*(位数-1)次；
 */

class Solution {
public:
    int powerbase10(unsigned int n){
        int res = 1;
        while(n){
            res *= 10;
            n--;
        }
        return res;
    }
    
    int NumberOf1Between1AndN(const string &str,int index){
    if(str.size() == 0)    return 0;
    if(index == static_cast<int>(str.size()) - 1){
        if(str[index] == '0')
            return 0;
        return 1;
    }

    if(stoi(str.substr(index)) == 0)
        return 0;

    int count1,countOther;
    int length = str.size() - index;
    int firstDigit = str[index] - '0';

    if(firstDigit == 1)
        count1 = stoi(str.substr(index + 1)) + 1;
    else//大于1
        count1 = powerbase10(length - 1);

    countOther = firstDigit * (length - 1) * powerbase10(length - 2);
    int countRecursive = NumberOf1Between1AndN(str,index + 1);

    return count1 + countOther + countRecursive;
}
    
    int NumberOf1Between1AndN_Solution(int n)
    {
        string s = to_string(n);
        
        return NumberOf1Between1AndN(s,0);
    }
};