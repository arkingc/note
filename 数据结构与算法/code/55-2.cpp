/*
 * 1）遍历AVL的每个节点，求该节点左右子树的高度，如果差不超过1，则继续递归，
 *    判断左右子树是不是AVL（求深度时会重复遍历节点，效率低）
 * 2）后续遍历，遍历到一个节点时已经遍历了它的左右子树，只要在遍历每个节点的时候
 *    记录它的深度，就可以一边遍历一边判断每个节点是不是平衡的
 */

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