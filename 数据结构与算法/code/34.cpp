/*
 * 当用前序遍历的方式访问到某一节点时，把该节点添加到路径(vector)上，并累加该节点的值。
 * 如果节点为叶节点，并且路径中节点值的和刚好等于输入的整数，则当前路径符合要求，打印出来。
 * 如果不是叶节点，继续访问子节点。
 * 当前节点访问结束后，递归函数将自动回到它的父节点。因此，在函数退出之前要在路径上删除当前节点并减去当前节点的值，以确保返回父节点时路径刚好是从根节点到父节点。
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