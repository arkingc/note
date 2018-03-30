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
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(!pHead1)
            return pHead2;
        if(!pHead2)
            return pHead1;
        
        ListNode *l1 ,*l2,*tp,*head;
        l1 = pHead1->val < pHead2->val ? pHead1 : pHead2;
        l2 = l1 == pHead1 ? pHead2 : pHead1;
        head = l1;
        
        while(l1->next){
            if(l1->next->val > l2->val){
                tp = l1->next;
                l1->next = l2;
                l2 = tp;
            }
            else
                l1 = l1->next;
        }
        
        if(l2){
            l1->next = l2;
            l2 = l2->next;
        }
        
        return head;
    }
};