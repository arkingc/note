class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        int depth = 0;
        return IsBalanced_Solution(pRoot,depth);
    }
    
    bool IsBalanced_Solution(TreeNode* node,int &depth){
        if(!node){
            depth = 0;
            return true;
        }
        
        int depth1 = 0,depth2 = 0;
        bool res = true;
        
        if(node->left)
            res &= IsBalanced_Solution(node->left,depth1);
        if(res && node->right)
            res &= IsBalanced_Solution(node->right,depth2);
        
        if(res){
            if(depth1 - depth2 > -2 && depth1 - depth2 < 2)
                res = true;
            else
                res = false;
            depth = (depth1 > depth2) ? (depth1 + 1) : (depth2 + 1);
        }
        
        return res;
    }
};