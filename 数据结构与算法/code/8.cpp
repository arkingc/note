
/*
 * 如果一个节点有右子树，那么下一个节点就是它的右子树中的最左子节点；
 * 如果节点没有右子树，并且它是父节点的左子节点，则下一节点就是它的父节点；
 * 如果节点没有右子树，并且它是父节点的右子节点，则沿着指向父节点的指针一直向上遍历，直到找到一个是它父节点的左子节点。如果这样的节点存在，那么这个节点的父节点就是我们要找的下一个节点；​​​​
 */

/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if(!pNode)
            return nullptr;
        
        if(pNode->right)
            return MostLeft(pNode->right);
        
        TreeLinkNode* nd = pNode;
        while(nd->next && nd->next->left != nd)
            nd = nd->next;
        if(!nd->next)
            return nullptr;
        else
            return nd->next;
    }
    
    TreeLinkNode* MostLeft(TreeLinkNode* nd){
        if(!nd)
            return nullptr;
        
        if(!nd->left)
            return nd;
        
        return MostLeft(nd->left);
    }
};