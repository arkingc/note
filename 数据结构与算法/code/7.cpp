/*
 * 前序遍历的头为根节点，在中序遍历中找到根节点，根节点左侧为左子树节点，右边为右子树节点。
 * 前序遍历中根节点后的节点也是按左子树和右子树划分。因此可以分别得到左子树和右子树的前序遍历和中序遍历
 * 递归处理；
 */

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.empty() || vin.empty() || (pre.size() != vin.size())){
            return nullptr;
        }
        
        int sz1 = pre.size();
        int sz2 = vin.size();
        
        return reConstructBinaryTreeCore(pre,vin,0,sz1-1,0,sz2-1);
    }
    
    TreeNode* reConstructBinaryTreeCore(const vector<int> &pre,const vector<int> &vin
                                   ,int preL,int preR,int vinL,int vinR)
    {
        if(preL > preR)
            return nullptr;
        
        TreeNode *root = new TreeNode(pre.at(preL));
        
        int i = vinL;
        for (;i <= vinR;i++)
            if(vin.at(i) == pre.at(preL))
                break;
        
        int leftsz = i - vinL;
        int rightsz = vinR - i;
        
        root->left = reConstructBinaryTreeCore(pre,vin,preL+1,preL+leftsz,vinL,i-1);
        root->right = reConstructBinaryTreeCore(pre,vin,preL+leftsz+1,preR,i+1,vinR);
        
        return root;
    }
};