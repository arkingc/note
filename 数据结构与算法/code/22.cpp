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
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(k == 0 || !pListHead)//unsigned int肯定大于等于0
            return nullptr;
        
        int first = k - 1;
        ListNode *p1 = pListHead,*p2 = pListHead;
        while(p1->next && first){
            p1 = p1 -> next;
            first--;
        }
        
        if(first > 0)
            return nullptr;
        
        while(p1->next){
            p1 = p1->next;
            p2 = p2->next;
        }
        
        return p2;
    }
};