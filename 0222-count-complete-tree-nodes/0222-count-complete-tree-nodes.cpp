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
    pair<int,int> height(TreeNode* root){
        TreeNode* currentLeft = root;
        TreeNode* currentRight = root;
        int l = 0,r = 0;
        while(currentLeft){
            l++;
            currentLeft = currentLeft->left;
        }
        while(currentRight){
            r++;
            currentRight = currentRight->right;
        }
        return {l,r};
    }
    int countNodes(TreeNode* root){
        if(root == NULL) return 0;
        pair<int,int> m = height(root);
        int lh = m.first;
        int rh = m.second;
        if(lh == rh)  return ((1<<lh) -1);
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};