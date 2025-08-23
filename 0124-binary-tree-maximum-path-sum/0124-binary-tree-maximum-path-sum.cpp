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
    int maxSum = INT_MIN;
    int height(TreeNode* root){
        if(root == nullptr) return 0;
        int lsum = height(root->left);
        int rsum = height(root->right);
        maxSum = max(maxSum, lsum + rsum + root->val);
        return max(max(lsum,rsum) + root->val,0);
    }
    int maxPathSum(TreeNode* root) {
        height(root);
        return maxSum;
    }
};