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
        queue<pair<TreeNode*,long long>> q;
        q.push({root,0});
        long long maxWidth = 0;
        while(!q.empty()){
            int n = q.size();
            int minInd = q.front().second;
            long long ind;
            for(int i = 0; i < n; i++){
                pair<TreeNode*,int> qFront = q.front();
                q.pop();
                TreeNode* node = qFront.first;
                ind = qFront.second - minInd;
                if(node->left) q.push({node->left,2*ind + 1});
                if(node->right) q.push({node->right,2*ind + 2});
            }
            maxWidth = max(maxWidth,ind+1);
        }
        return maxWidth;
    }
};