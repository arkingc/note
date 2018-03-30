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
        
        if(!nd->left && !nd->right)
            return nd;
        
        if(!nd->left)
            return nd;
        
        return MostLeft(nd->left);
    }
};