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
    int maxi = 0;
    int diameter(TreeNode* root){
        if(root==nullptr) return 0;
        int d1 = diameter(root->left);
        int d2 = diameter(root->right);
        maxi = max(maxi,d1+d2);
        return max(d1,d2)+1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        diameter(root);
        return maxi;
    }
};