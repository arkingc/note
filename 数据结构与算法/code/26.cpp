/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(!pRoot1 || !pRoot2)
            return false;
        
        bool res = false;
        if(pRoot1->val == pRoot2->val)    res = SameTree(pRoot1->left,pRoot2->left) && SameTree(pRoot1->right,pRoot2->right);
        if(res)    return true;
        
        res = HasSubtree(pRoot1->left,pRoot2) || HasSubtree(pRoot1->right,pRoot2);
        return res;
    }
    
    bool SameTree(TreeNode* pRoot1,TreeNode* pRoot2)
    {
        if(!pRoot2)    return true;
        if(!pRoot1)    return false;
        
        if(pRoot1->val == pRoot2->val)    return SameTree(pRoot1->left,pRoot2->left) && SameTree(pRoot1->right,pRoot2->right);
        return false;
    }
};