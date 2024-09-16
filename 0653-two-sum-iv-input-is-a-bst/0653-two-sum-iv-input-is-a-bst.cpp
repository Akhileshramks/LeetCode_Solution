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
    vector<int> inorder;
    void inorderTraversal(TreeNode* root){
        if(root == NULL) return;
        inorderTraversal(root->left);
        inorder.push_back(root->val);
        inorderTraversal(root->right);
    }
    bool findTarget(TreeNode* root, int k) {
        inorderTraversal(root);
        int n = inorder.size();
        int low = 0,high = n-1;
        while(low < high){
            if(inorder[low] + inorder[high] == k) return true;
            else if(inorder[low] + inorder[high] < k) low++;
            else high--;
        }
        return false;
    }
};