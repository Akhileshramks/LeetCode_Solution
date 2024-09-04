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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        queue<TreeNode*> q;
        q.push(root);
        vector<vector<int>> zigLevel;
        int level = 1;
        while(!q.empty()){
            int n = q.size();
            vector<int> levelNode(n);
            for(int i =0;i<n;i++){
                TreeNode* node = q.front();
                q.pop();
                int ind = level == 1 ? i : n-i-1;
                levelNode[ind] = node->val;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            level = !level;
            zigLevel.push_back(levelNode);
        }
        return zigLevel;
    }
};