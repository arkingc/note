class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if(numbers.size() == 0)
            return 0;
        
        int count = 0;
        int res = numbers[0];
        for(int e : numbers){
            if(e == res)
                count++;
            else{
                if(count == 0)
                    res = e;
                else
                    count--;
            }
        }
        
        count = 0;
        for(int i = 0;i < numbers.size();i++){
            if(numbers[i] == res)
                count++;
        }
        if(count * 2 <= numbers.size())
            return 0;
        return res;
    }
};