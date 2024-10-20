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
    int pathSum = INT_MIN;
    int maxPath(TreeNode* root){
        if(root == NULL) return 0;
        int leftSum = max(0,maxPath(root->left));
        int rightSum = max(0,maxPath(root->right));
        pathSum = max(root->val + leftSum + rightSum , pathSum);
        return max(leftSum,rightSum)+root->val;
    }
    int maxPathSum(TreeNode* root) {
        maxPath(root);
        return pathSum;
    }
};