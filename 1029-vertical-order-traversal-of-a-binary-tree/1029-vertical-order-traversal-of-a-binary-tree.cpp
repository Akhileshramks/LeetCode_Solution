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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int,map<int,multiset<int>>> levelOrder;
        queue<pair<int,pair<int,TreeNode*>>> q;
        q.push({0,{0,root}});
        while(!q.empty()){
            int n = q.size();
            for(int i = 0;i < n;i++){
                auto front = q.front();
                q.pop();
                levelOrder[front.second.first][front.first].insert(front.second.second->val);
                if(front.second.second->left) q.push({front.first + 1,{front.second.first - 1,front.second.second->left}});
                if(front.second.second->right) q.push({front.first + 1,{front.second.first + 1,front.second.second->right}});
            }
        }
        vector<vector<int>> ans;
        for(auto i : levelOrder){
            vector<int> intermediate;
            for(auto j : i.second){
                for(auto k : j.second) intermediate.push_back(k);
            }
            ans.push_back(intermediate);
        }
        return ans;
    }
};