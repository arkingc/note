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