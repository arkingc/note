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