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
        
        return SameTree(pRoot1,pRoot2) || HasSubtree(pRoot1->left,pRoot2) || HasSubtree(pRoot1->right,pRoot2);
    }
    
    //在pRoot1中查找是否包含和pRoot2相同的子树
    bool SameTree(TreeNode* pRoot1,TreeNode* pRoot2)
    {
        //存在空节点时
        if(!pRoot1 || !pRoot2)
            return (!pRoot1 && !pRoot2) ? true : false;
        
        //不存在空节点，但不相等
        if(pRoot1->val != pRoot2->val)
            return false;
        
        bool res = true;
        
        if(pRoot2->left)
            res &= HasSubtree(pRoot1->left,pRoot2->left);
        
        //如果左子树已经不满足则不必比较右子树
        if(res && pRoot2->right)
            res &= HasSubtree(pRoot1->right,pRoot2->right);
        
        return res;
    }
};