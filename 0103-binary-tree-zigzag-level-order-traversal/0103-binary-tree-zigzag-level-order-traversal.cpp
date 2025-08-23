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
    void dfs(vector<vector<int>> &ans, TreeNode* root,int l){
        if(root == nullptr) return;
        if(ans.size() == l){
            ans.push_back({});
        }
        if(l % 2 == 0){
            ans[l].push_back(root->val);
        }else{
            ans[l].push_back(root->val);
        }
        dfs(ans, root->left, l+1);
        dfs(ans, root->right, l+1);
    }
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        dfs(ans, root, 0);
        bool zigZag = false;
        for(auto &i : ans){
            if(zigZag) reverse(i.begin(),i.end());
            zigZag = !zigZag;
        }
        return ans;
    }
};