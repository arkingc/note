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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> res;
        if(!root)
            return res;
        
        deque<TreeNode*> q;
        q.push_back(root);
        
        TreeNode *curr;
        while(!q.empty()){
            curr = q.front();
            res.push_back(curr->val);
            q.pop_front();
            
            if(curr->left)
                q.push_back(curr->left);
            if(curr->right)
                q.push_back(curr->right);
        }
        
        return res;
    }
};