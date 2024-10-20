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
        vector<vector<int>> res;
        queue<pair<TreeNode*,pair<int,int>>> q;
        map<int,map<int,multiset<int>>> levelOrder;
        q.push({root,{0,0}});
        while(!q.empty()){
            int n = q.size();
            for(int i = 0; i < n; i++){
                pair<TreeNode*,pair<int,int>> qFront = q.front();
                TreeNode* node = qFront.first;
                int x = qFront.second.first;
                int y = qFront.second.second;
                q.pop();
                levelOrder[y][x].insert(node->val);
                if(node->left) q.push({node->left,{x+1,y-1}});
                if(node->right) q.push({node->right,{x+1,y+1}});
            }
        }
        for(auto & i : levelOrder){
            vector<int> level;
            for(auto &j : i.second){
                level.insert(level.end(),j.second.begin(),j.second.end());
            }
            res.push_back(level);
        }
        return res;
    }
};