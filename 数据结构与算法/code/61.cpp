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