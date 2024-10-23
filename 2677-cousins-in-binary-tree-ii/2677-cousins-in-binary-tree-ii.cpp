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
    TreeNode* replaceValueInTree(TreeNode* root) {
        int currentLevelSum = root->val;
        queue<pair<TreeNode*,int>> q;
        q.push({root,root->val});
        while(!q.empty()){
            int n = q.size();
            int nextLevelSum = 0;
            for(int i = 0;i < n;i++){
                TreeNode* node = q.front().first;
                int siblingsSum = q.front().second;
                q.pop();
                int childSum = 0;
                childSum += node->left ? node->left->val : 0;
                childSum += node->right ? node->right->val : 0;
                if(node->left) q.push({node->left,childSum});
                if(node->right) q.push({node->right,childSum});
                node->val = currentLevelSum - siblingsSum;
                nextLevelSum += childSum;
            }
            currentLevelSum = nextLevelSum;
        }
        return root;
    }
    
};