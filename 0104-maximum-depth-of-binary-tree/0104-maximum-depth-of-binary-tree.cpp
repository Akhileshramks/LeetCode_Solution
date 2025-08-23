/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxHeight = 1;
    void dfs(TreeNode* root,int h){
        maxHeight = max(maxHeight, h);
        if(root->left) dfs(root->left,h+1);
        if(root->right) dfs(root->right,h+1);
    }
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        dfs(root,1);
        return maxHeight;
    }
};