/*
 * 入队：插入stack1；
 * 出队：如果stack2为空，从stack1弹出并压入stack2，最后弹出stack2栈顶。如果stack2不为空，直接弹出​stack2栈顶；
 */

class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty()){
            while(!stack1.empty()){
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        if(stack2.empty())
            throw new exception();
        int front;
        front = stack2.top();
        stack2.pop();
        return front;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};