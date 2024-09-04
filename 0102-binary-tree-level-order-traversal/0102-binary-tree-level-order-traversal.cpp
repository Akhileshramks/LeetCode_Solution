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
    void levelOrderTraversal(TreeNode* root,vector<vector<int>> &res,int level){
        if(root == NULL) return;
        if(res.size()>level) res[level].push_back(root->val);
        else res.push_back({root->val});
        levelOrderTraversal(root->left,res,level+1);
        levelOrderTraversal(root->right,res,level+1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        levelOrderTraversal(root,res,0);
        return res;
    }
};