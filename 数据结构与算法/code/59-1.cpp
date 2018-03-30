class Solution {
public:
    vector<int> maxInWindows(const vector<int>& num, unsigned int size)
    {
        vector<int> res;
        if(size > num.size())
            return res;
        
        deque<int> dq;
        int sz = num.size();
        for(int i = 0;i < sz;i++){
            while(dq.size() > 0 && num[dq.back()] < num[i])
                dq.pop_back();
            dq.push_back(i);
            if(i - dq.front() + 1 > size)
                dq.pop_front();
            if(i >= size - 1)
                res.push_back(num[dq.front()]);
        }
        
        return res;
    }
};