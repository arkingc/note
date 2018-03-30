class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if(pushV.size() != popV.size())
            return false;
        
        stack<int> st;
        int i = 0;
        for(int e : popV){
            if(!st.empty() && st.top() == e){
                st.pop();
                continue;
            }
            while(i < pushV.size() && pushV[i] != e){
                st.push(pushV[i]);
                i++;
            }
            if(i == pushV.size())
                return false;
            i++;
        }
        
        return true;
    }
};