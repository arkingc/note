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
    vector<vector<int> > Print(TreeNode* pRoot) {
        vector<vector<int> > res;
        if(!pRoot)
            return res;
        
        stack<TreeNode*> st[2];
        int index = 0;//0的栈存从左到右的节点，1存从右到左
        st[index].push(pRoot);
        
        TreeNode* curr;
        vector<int> linevec;
        while(!st[index].empty()){
            curr = st[index].top();
            st[index].pop();
            linevec.push_back(curr->val);
            
            if(!index){
                if(curr->left)
                    st[1-index].push(curr->left);
                if(curr->right)
                    st[1-index].push(curr->right);
            }
            else{
                if(curr->right)
                    st[1-index].push(curr->right);
                if(curr->left)
                    st[1-index].push(curr->left);
            }
            
            //如果是最后一个元素
            if(st[index].empty()){
                index = 1 - index;
                res.push_back(linevec);
                linevec.clear();
            }
        }
        
        return res;
    }
};