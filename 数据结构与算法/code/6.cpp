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