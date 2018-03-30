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
    int TreeDepth(TreeNode* pRoot)
    {
        if(!pRoot)
            return 0;
        
        int depth1 = 1 + TreeDepth(pRoot->left);
        int depth2 = 1 + TreeDepth(pRoot->right);
        
        return depth1 > depth2 ? depth1 : depth2;
    }
};