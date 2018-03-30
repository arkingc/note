/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/
class Solution {
public:
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
        if(!pRoot || k <= 0)
            return nullptr;
        
        int count = 0;
        return KthNode(pRoot,k,count);
    }

    TreeNode* KthNode(TreeNode* pRoot,int k,int &count){
        if(!pRoot)
            return nullptr;
        
        TreeNode* nd;
        if(pRoot->left){
            nd = KthNode(pRoot->left,k,count);
            if(nd)
                return nd;
        }
        if(++count == k)
            return pRoot;
        if(pRoot->right){
            nd = KthNode(pRoot->right,k,count);
            if(nd)
                return nd;
        }
        
        return nullptr;
    }
};