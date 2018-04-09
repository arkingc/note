/*
 * n(1) -> n(2) -> ... -> n(k) -> n(k+1) <- ... <- n(m)
 * 
 * 在m个节点的链表中，对于每次递归处理的节点k，假设节点k之后的节点已经处理完（逆序）。
 * 对于节点k，只需修改其next成员，以及节点(k+1)的next成员:
 *    n(k)->next->next = n(k);
 *    n(k)->next = NULL;
 *
 * 函数返回逆序后链表的头结点，因此对于n(m)，直接返回n(m)
 */

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
        
        ReverseListCore(pHead->next);
        pHead->next->next = pHead;
        pHead->next = nullptr;
    }
};