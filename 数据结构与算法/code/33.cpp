/*
 * 左->右->根  ---> 小->大->中
 * 首先判断序列是否满足这种大小关系，然后递归处理子树；
 *
 * 扩展：判断数组是不是某二叉搜索树的前序遍历结果；
 */

class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        int sz = sequence.size();
        
        if(sz == 0)
            return false;
        
        return VerifySquenceOfBST(sequence,0,sz-1);
    }
    
    bool VerifySquenceOfBST(const vector<int> &sequence,int l,int r){
        if(l >= r)
            return true;
        
        int m,tp = l;
        int root = sequence.at(r);
        while(tp < r && sequence.at(tp++) < root){}
        if(tp < r){
            tp = tp - 1;
            m = tp;
            while(tp < r){
                if(sequence.at(tp) < root){
                    return false;
                }
                tp++;
            }
        }
        
        return VerifySquenceOfBST(sequence,l,m-1) && VerifySquenceOfBST(sequence,m,r-1);
        
    }
};