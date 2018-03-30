class Solution {
public:
    int LastRemaining_Solution(int n, int m)
    {
        if(n <= 0 || m <= 0)
            return -1;

        list<int> ls;

        for(int i = 0;i < n;i++)
            ls.push_back(i);

        list<int>::iterator it = ls.begin();
        while(n > 1){
            int tp = m - 1;
            while(tp){
                if(it == ls.end())
                    it = ls.begin();
                it++;
                if(it == ls.end())
                    it = ls.begin();
                tp--;
            }
            it = ls.erase(it);
            n--;
        }

        if(it == ls.end())
            it = ls.begin();

        return *it;
    }
};