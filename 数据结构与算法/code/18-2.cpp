/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        if(!pHead)
            return nullptr;
        
        ListNode *p = pHead,*tp,*prev = nullptr;
        while(p && p->next){//遍历到倒数第二个节点
            if(!(p->next) || p->next->val != p->val){//如果没有下一个节点或者下一个节点与当前遍历的节点的值不等
                prev = p;
                p = p->next;
                continue;
            }
            
            while(p->next && p->val == p->next->val){//对于每个节点，只要还有下一个节点，并且下一个节点相同，则删除下一节点
                tp = p->next;
                p->next = p->next->next;
                tp->next = nullptr;
                delete tp; 
            }
            
            //到此，说明当前遍历的节点存在重复，并且已经删除了其后的所有重复，需要再删除当前节点
            if(!prev){//说明链表的头结点就存在重复，需要删除头结点
                pHead = p->next;
                p->next = nullptr;
                delete p;
                p = pHead;
            }
            else{
                prev->next = p->next;
                p->next = nullptr;
                delete p;
                p = prev->next;
            }
        }
        
        return pHead;
    }
};