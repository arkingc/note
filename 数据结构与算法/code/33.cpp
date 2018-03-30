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