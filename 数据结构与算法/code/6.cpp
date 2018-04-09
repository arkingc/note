/*
 * 1）反序，再打印（但会修改链表）；
​ * 2）使用一个栈（鲁棒性好）；
 * 3）递归（递归本质上就是一个栈结构，但是链表过长时可能栈溢出）​；
 */

/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        if(!head)
            return vector<int>();
        
        vector<int> res;
        printListFromTailToHead(head,res);
        
        return res;
    }
    
    void printListFromTailToHead(ListNode* head,vector<int> &res){
        if(!head)
            return;
        
        printListFromTailToHead(head->next,res);
        res.push_back(head->val);
    }
};