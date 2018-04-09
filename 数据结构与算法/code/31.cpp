/*
 * 如果下一个弹出的数字刚好是栈顶数字，那么直接弹出；
 * 如果下一个弹出的数字不在栈顶，则把压栈序列中还没有入栈的数字压入栈中，直到把下一个需要弹出的数字压入栈顶为止；
 * 如果所有数字都压入栈后仍然没有找到下一个弹出的数字，那么该序列不可能是一个弹出序列；
 */

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