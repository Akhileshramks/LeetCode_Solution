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
    int heightLeft(TreeNode* root){
        int count = 0;
        while(root){
            count++;
            root = root -> left;
        }
        return count;
    }
    int heightRight(TreeNode* root){
        int count = 0;
        while(root){
            count++;
            root = root -> right;
        }
        return count;
    }
    int countNodes(TreeNode* root) {
        if(root == NULL) return 0;
        int left = heightLeft(root);
        int right = heightRight(root);
        if(left == right){
            return (1<<left)-1;
        }
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};