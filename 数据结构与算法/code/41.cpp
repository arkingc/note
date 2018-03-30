class Solution {
public:
    void Insert(int num)
    {
        if(index % 2 == 0){
            if(max.size() > 0 && num < max[0]){
                max.push_back(num);
                push_heap(max.begin(),max.end(),less<int>());
                
                num = max[0];
                pop_heap(max.begin(),max.end(),less<int>());
                max.pop_back();
            } 
            min.push_back(num);
            push_heap(min.begin(),min.end(),greater<int>());
        }
        else{
            if(min.size() > 0 && num > min[0]){
                min.push_back(num);
                push_heap(min.begin(),min.end(),greater<int>());
                
                num = min[0];
                
                pop_heap(min.begin(),min.end(),greater<int>());
                min.pop_back();
            }
            max.push_back(num);
            push_heap(max.begin(),max.end(),less<int>());
        }
        
        index++;
    }

    double GetMedian()
    {
        double median = 0;
        if(index % 2 == 1){
            median = min[0];
        }
        else{
            median = (min[0] + max[0])/(2.0);
        }
        return median;
    }

private:
    vector<int> max;
    vector<int> min;
    int index = 0;
};