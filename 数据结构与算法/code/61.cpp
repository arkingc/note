/*
 * 首先把数组排序，
 * 其次统计数组中0的个数；
 * 最后统计排序之后的数组中相邻数字之间的空缺总数。如果空缺的总数小于或等于0的个数，那么这个数组就是连续的；
 * （还需注意，如果数组中的非0数字重复出现，则该数组不是连续的）；​​
 */

class Solution {
public:
    bool IsContinuous( vector<int> numbers ) {
        if(numbers.size() == 0)
            return false;
        
        sort(numbers.begin(),numbers.end());
        
        int numOfZero = 0;
        for(int e : numbers){
            if(e == 0)
                numOfZero++;
            else if(e < 0 || e > 13)
                return false;
        }
        if(numOfZero > 4)
            return false;
        
        int bgidx = numOfZero;
        for(int i = bgidx + 1;i < numbers.size();i++){
            if(numbers[i] - numbers[i - 1] == 0)
                return false;
            else if(numbers[i] - numbers[i - 1] > 1){
                if(numOfZero >= (numbers[i] - numbers[i - 1] -1))
                    numOfZero -= numbers[i] - numbers[i - 1] - 1;
                else
                    return false;
            }
        }
        
        return true;
    }
};