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
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        if(!pHead)
            return nullptr;

        ListNode *p1 = pHead,*p2 = pHead;
        while(true){
            p1 = p1->next;
            p2 = p2->next;
            if(p2)    {p2 = p2->next;}
            if(!p2)    return nullptr;//由于p2走得快，如果链表无环，肯定会在这里返回

            if(p1 == p2)    break;
        }

        int circleLength = 1;
        p2 = p2->next;
        while(p2 != p1)    {circleLength++;p2 = p2->next;}

        p1 = pHead,p2 = pHead;
        while(circleLength){
            p2 = p2->next;
            circleLength--;
        }
        while(p1 != p2){
            p1 = p1->next;
            p2 = p2->next;
        }

        return p1;
    }
};