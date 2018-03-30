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
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        vector<vector<int>> pathArr;
        if(!root)
            return pathArr;
        
        vector<int> path;
        FindPathCore(root,expectNumber,path,pathArr);
        return pathArr;
    }
    
    void FindPathCore(TreeNode* nd,int expectNumber,
                      vector<int> &path,vector<vector<int>> &pathArr){
        if(!nd)
            return;
        
        path.push_back(nd->val);
        expectNumber -= nd->val;
        
        if(nd->left)
            FindPathCore(nd->left,expectNumber,path,pathArr);
        if(nd->left)
            FindPathCore(nd->right,expectNumber,path,pathArr);
        
        if(!nd->left && !nd->right && expectNumber == 0){
            pathArr.push_back(path);
        }
        
        path.pop_back();
    }
};