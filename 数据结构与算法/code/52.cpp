/*
 * 1）蛮力法（O(n^2)）
 * 2）两个辅助栈（从尾部比较，找到最后一个相同节点，就是第一个公共节点）（O(m+n)，需要同样的空间代价）
 * 3）长链表先走长度之差步，然后同时遍历，找到第一个相同节点（O(m+n)）​​
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