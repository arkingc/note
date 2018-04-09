/*
 * 使用一个两端队列，队列头部始终保存当前滑动窗口最大值。
 * 对于数组中任意元素，从尾部向前比较，如果该元素大于尾部元素，则从队列尾部删除，一直删除完所有比新元素小的元素，然后从尾部插入新元素(的下标)。
 * 由于新元素不一定比首元素大，如果首元素刚好从滑动窗口移除时，也要删除首元素，所以在完成上述操作后，也要判断首元素是否已经脱离滑动窗口
 * 因为要判断队首元素是否脱离滑动窗口，所以队列存的是元素的下标，同时要从首部删除，所以使用双端队列；
 */

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