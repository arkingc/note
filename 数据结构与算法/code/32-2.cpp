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
            
            deque<TreeNode*> dq;
            dq.push_back(pRoot);
            
            vector<int> linevec;
            int currleft = 1,nextlinecount = 0;
            TreeNode* curr;
            while(currleft != 0){
                curr = dq.front();
                dq.pop_front();
                currleft--;
                linevec.push_back(curr->val);
                
                if(curr->left){
                    dq.push_back(curr->left);
                    nextlinecount++;
                }
                if(curr->right){
                    dq.push_back(curr->right);
                    nextlinecount++;
                }
                
                if(currleft == 0){
                    res.push_back(linevec);
                    linevec.clear();
                    currleft = nextlinecount;
                    nextlinecount = 0;
                }
            }
            return res;
        }
};