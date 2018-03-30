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
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        TreeNode *last = nullptr;
        
        ConvertCore(pRootOfTree,&last);
        
        while(last && last->left){
            last = last->left;
        }
        
        return last;
    }
    
    void ConvertCore(TreeNode* pRootOfTree,TreeNode **last)
    {
        if(!pRootOfTree)
            return;
        
        ConvertCore(pRootOfTree->left,last);
        pRootOfTree->left = *last;
        if(*last)
            (*last)->right = pRootOfTree;
        *last = pRootOfTree;
        ConvertCore(pRootOfTree->right,last);
    }
};