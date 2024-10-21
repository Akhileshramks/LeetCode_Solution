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
    TreeNode* removeTargetLeaf(TreeNode* root,int target){
        if(!root) return root;
        if(root->left){
            root->left = removeTargetLeaf(root->left,target);
        }
        if(root->right){
            root->right = removeTargetLeaf(root->right,target);
        }
        if(root->left == NULL && root->right == NULL && root->val == target) return NULL;
        return root;
    }
    TreeNode* removeLeafNodes(TreeNode* root, int target) {
        return removeTargetLeaf(root,target);
    }
};