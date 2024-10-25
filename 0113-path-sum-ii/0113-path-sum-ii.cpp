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
    vector<vector<int>> res;
    void dfs(TreeNode* root,int target,int currentSum,vector<int> path){
        if(!root) return;
        currentSum += root->val;
        path.push_back(root->val);
        if(target -  currentSum == 0 && !root->left && !root->right) res.push_back(path);
        if(root->left) dfs(root->left,target,currentSum,path);
        if(root->right) dfs(root->right,target,currentSum,path);
        path.pop_back();
        return;
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> path;
        dfs(root,targetSum,0,path);
        return res;
    }
};