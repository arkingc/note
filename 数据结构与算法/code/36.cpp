/*
 * 中序遍历，​​当前节点之前的节点已经处理好，使用一个变量(全局)保存链表的最后一个节点，
 * 对当前节点，处理它和链表最后一个节点的指向关系，并更新最后一个节点的全局变量。
 * 这个全局变量使用指针的指针，如果使用指针，函数调用修改的形参last指针，调用返回后实参last并未修改；
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
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        TreeNode *last = nullptr;
        
        ConvertCore(pRootOfTree,&last);
        
        while(last && last->left){
            last = last->left;
        }
        
        return last;
    }
    
    void ConvertCore(TreeNode* pRootOfTree,TreeNode **last)
    {
        if(!pRootOfTree)
            return;
        
        ConvertCore(pRootOfTree->left,last);
        pRootOfTree->left = *last;
        if(*last)
            (*last)->right = pRootOfTree;
        *last = pRootOfTree;
        ConvertCore(pRootOfTree->right,last);
    }
};