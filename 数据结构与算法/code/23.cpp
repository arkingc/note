/*
 * 两个指针，1个1步，1个2步，在环中相遇，记录相遇节点，再遍历到此节点，计算出环长；
 * 然后再用2个指针，1个先走环长步，然后两个一起走，会在入口节点相遇；​
 */

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