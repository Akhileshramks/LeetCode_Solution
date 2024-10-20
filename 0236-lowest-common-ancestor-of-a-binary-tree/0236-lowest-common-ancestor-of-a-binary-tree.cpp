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
    TreeNode* res = NULL;
    bool lca(TreeNode* root,TreeNode* p,TreeNode* q){
        if(root == NULL) return false;
        bool curr = root == p || root == q;
        bool l = lca(root->left,p,q);
        bool r = lca(root->right,p,q);
        if(l && r || (curr && (l || r))) res = root;
        return l || r || curr;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        lca(root,p,q);
        return res;
    }
};