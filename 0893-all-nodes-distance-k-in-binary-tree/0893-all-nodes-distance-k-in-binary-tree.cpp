/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void linkParent(TreeNode* root,unordered_map<TreeNode*,TreeNode*> &parent){
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            if(node->left){
                parent[node->left] = node;
                q.push(node->left);
            }
            if(node->right){
                parent[node->right] = node;
                q.push(node->right);
            }
        }
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<TreeNode*,TreeNode*> parent;
        linkParent(root,parent);
        unordered_map<TreeNode*,bool> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited[target] = true;
        int cnt = 0;
        vector<int> res;
        while(!q.empty() && cnt<k){
            int n = q.size();
            cnt++;
            for(int i = 0;i<n;i++){
                TreeNode* node = q.front();
                q.pop();
                if(node->left && !visited[node->left]){
                    q.push(node->left);
                    visited[node->left] = true;
                } 
                if(node -> right && !visited[node -> right]){
                    q.push(node->right);
                    visited[node->right] = true;
                }
                if(parent[node] && !visited[parent[node]]){
                    q.push(parent[node]);
                    visited[parent[node]] = true;
                } 
            }
        }
        while(!q.empty()){
            res.push_back(q.front()->val);
            q.pop();
        }
        return res;
    }
};