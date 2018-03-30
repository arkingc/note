/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if(!pHead)
            return nullptr;
        
        ListNode *head = pHead;
        while(head->next)    head = head->next;
        
        ReverseListCore(pHead);
        return head;
    }
    
    void ReverseListCore(ListNode* pHead){
        if(!(pHead->next)){
            return;
        }
        
        ReverseList(pHead->next);
        pHead->next->next = pHead;
        pHead->next = nullptr;
    }
};