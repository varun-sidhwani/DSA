/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* r, TreeNode* p, TreeNode* q) {
        if(!r)
            return r;
        if(r->val == p->val || r->val==q->val)
            return r;
        
        TreeNode* left = lowestCommonAncestor(r->left,p,q);
        TreeNode* right = lowestCommonAncestor(r->right,p,q);
        
        if(left && right)
            return r;
        
        return left ? left : right;//keep searching in left or right

    }
};