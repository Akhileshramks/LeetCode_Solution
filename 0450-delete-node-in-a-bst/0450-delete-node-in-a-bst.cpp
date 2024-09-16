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
    TreeNode* inorderSuccessor(TreeNode* root){
        while(root->right) root = root->right;
        return root;
    }
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == NULL) return NULL;
        if(root->val == key){
            if(root->left == NULL && root->right == NULL) return NULL;
            else{
                if(root->left == NULL)  return root->right;
                else if(root->right == NULL) return root->left;
                else{
                    TreeNode* inOrderSuceessor = inorderSuccessor(root->left);
                    deleteNode(root,inOrderSuceessor->val);
                    root->val = inOrderSuceessor->val;
                    return root;
                }
            }
        }
        else if(root->val > key) root->left = deleteNode(root->left,key);
        else root->right = deleteNode(root->right,key);
        return root;
    }
};