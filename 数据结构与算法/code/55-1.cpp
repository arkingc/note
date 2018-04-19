/*
 * 如果只有一个节点，深度为1；
 * 如果根节点只有左子树，深度为左子树加1；
 * 如果只有右子树，深度为右子树加1；
 * 如果都有，深度为左子树和右子树深度较大者加1
 */

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