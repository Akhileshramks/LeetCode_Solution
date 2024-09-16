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
    int kSmallest = 0;
    void inOrder(TreeNode* root,int k,int& count){
        if(!root || count>k) return;
        inOrder(root->left,k,count);
        count++;
        if(count == k) kSmallest = root->val;
        inOrder(root->right,k,count);
    }
    int kthSmallest(TreeNode* root, int k) {
        int count = 0;
        inOrder(root,k,count);
        return kSmallest;
    }
};