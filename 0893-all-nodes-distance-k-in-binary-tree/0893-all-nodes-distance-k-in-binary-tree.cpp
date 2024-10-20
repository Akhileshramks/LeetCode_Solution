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
    void linkParent(TreeNode* root,unordered_map<TreeNode*,TreeNode*>& parent){
        if(root == NULL) return;
        if(root->left){
            parent[root->left] = root;
            linkParent(root->left,parent);
        }
        if(root->right){
            parent[root->right] = root;
            linkParent(root->right,parent);
        }
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        queue<TreeNode*> q;
        int cnt = 0;
        unordered_map<TreeNode*,TreeNode*> parent;
        unordered_map<TreeNode*,bool> visited;
        linkParent(root,parent);
        vector<int> res;
        q.push(target);
        visited[target] = true;
        while(!q.empty() && cnt < k){
            int n = q.size();
            cnt++;
            for(int i =0;i<n;i++){
                TreeNode* node = q.front();
                q.pop();
                if(node->left && !visited[node->left]){
                    q.push(node->left);
                    visited[node->left] = true;
                }
                if(node->right && !visited[node->right]){
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