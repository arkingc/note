/*
 * 两步
 * 1）复制原始链表上的每个节点，用m_pNext链接起来；
 * 2）设置复制链表每个节点的random成员；
 * 
 * 不用辅助空间实现：复制的节点链接在原节点之后；​​​​​​
 */

/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(!pHead)
            return nullptr;
        
        map<RandomListNode*,RandomListNode*> relationRMap,relationMap;
        
        RandomListNode* p = pHead;
        RandomListNode *node = new RandomListNode(p->label);
        relationRMap[p] = node;
        relationMap[node] = p;
        RandomListNode *head = node;
        
        while(p->next){
            RandomListNode *nextnode = new RandomListNode(p->next->label);
            node->next = nextnode;
            node = nextnode;
            
            relationRMap[p->next] = nextnode;
            relationMap[nextnode] = p->next;
            
            p = p->next;
        }
        
        p = head;
        while(p){
            if(relationMap.find(p)->second->random)
                p->random = relationRMap.find(relationMap.find(p)->second->random)->second;
            p = p->next;
        }
        
        return head;
    }
};