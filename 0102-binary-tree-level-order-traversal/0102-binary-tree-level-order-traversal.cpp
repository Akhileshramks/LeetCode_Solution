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
    map<int,vector<int>> m;
    vector<vector<int>> res;
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(!root){
            return res;
        }
        queue<pair<TreeNode*,int>> q;
        q.push({root,0});
        pair<TreeNode*,int> p;
        while(!q.empty()){
            p = q.front();
            q.pop();
            m[p.second].push_back(p.first->val);
            if(p.first->left) q.push({p.first->left,p.second+1});
            if(p.first->right) q.push({p.first->right,p.second+1});
        }
        
        for(auto i : m){
            res.push_back(i.second);
        }
        return res;
    }
};