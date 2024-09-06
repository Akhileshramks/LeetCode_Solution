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
    int widthOfBinaryTree(TreeNode* root) {
        if(root == NULL) return 0;
        queue<pair<TreeNode*,long long>> q;
        q.push({root,0});
        int last_ind = 0;
        int first = 0;
        int ans = 0;
        while(!q.empty()){
            int n = q.size();
            int min_ind = q.front().second;
            for(int i = 0;i<n;i++){
                TreeNode* node = q.front().first;
                int ind = q.front().second;
                q.pop();
                long long curr_ind = ind - min_ind;
                if(node->left) q.push({node->left,2*curr_ind+1});
                if(node->right) q.push({node->right,2*curr_ind+2});
                if(i == n-1) last_ind = curr_ind;
            }
            ans = max(ans,last_ind+1);
        }
        return ans;
    }
};