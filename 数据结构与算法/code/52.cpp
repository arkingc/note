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
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(!pHead1 || !pHead2)
            return nullptr;
        
        ListNode *p1 = pHead1,*p2 = pHead2;
        int switchCount = 0;
        while(p1 && p2){
            if(!(p1->next) && switchCount < 2){
                p1 = pHead2;
                switchCount++;
            }
            if(!(p2->next) && switchCount < 2){
                p2 = pHead1;
                switchCount++;
            }
            
            if(switchCount == 2 && p1 == p2)    return p1;
            p1 = p1->next;
            p2 = p2->next;
        }
        
        return nullptr;
    }
};