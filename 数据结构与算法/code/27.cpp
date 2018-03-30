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
    void Mirror(TreeNode *pRoot) {
        stack<TreeNode*> st;
        if(pRoot)
            st.push(pRoot);
        
        TreeNode *curr,*tp;
        while(!st.empty()){
            curr = st.top();
            st.pop();
            
            tp = curr->left;
            curr->left = curr->right;
            curr->right = tp;
            
            if(curr->left)
                st.push(curr->left);
            if(curr->right)
                st.push(curr->right);
        }
    }
};