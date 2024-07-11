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
    void maxdepth(TreeNode* root,int c){
        if(root!=NULL){
            if(root->left) maxdepth(root->left,c+1);
            if(root->right) maxdepth(root->right,c+1);
            maxi = max(c,maxi);
        }
    }
    int maxDepth(TreeNode* root) {
        maxdepth(root,1);
        return maxi;
    }
};