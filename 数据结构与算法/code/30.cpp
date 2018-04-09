/*
 * 压入新值时，如果最小值不变，继续向辅助栈中压入旧min值，否则压入新值；
 */

class Solution {
public:
    void push(int value) {
        dataStack.push(value);
        if(minStack.empty() || !minStack.empty() && value < minStack.top()){
            minStack.push(value);
        }
        else
            minStack.push(minStack.top());
    }
    void pop() {
        if(dataStack.empty())
            throw new exception();
        dataStack.pop();
        minStack.pop();
    }
    int top() {
        if(dataStack.empty())
            throw new exception();
        return dataStack.top();
    }
    int min() {
        if(dataStack.empty())
            throw new exception();
        return minStack.top();
    }
private:
    stack<int> dataStack;
    stack<int> minStack;
};