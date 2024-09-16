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
    TreeNode* insertIntoBST(TreeNode* root1, int val) {
        TreeNode* root = root1;
        if(!root) return new TreeNode(val);
        while(root){
            if(root->val > val){
                if(root->left == nullptr){
                    root->left = new TreeNode(val);
                    return root1;;
                }
                else root = root->left;

            }
            else{
                if(root->right == nullptr){
                    root->right = new TreeNode(val);
                    return root1;
                }
                else root = root->right;
            }
        }
        return root1;
    }
};