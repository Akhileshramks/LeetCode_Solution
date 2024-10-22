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
    long long kthLargestLevelSum(TreeNode* root, int k) {
        queue<TreeNode*> q;
        q.push(root);
        priority_queue<long long,vector<long long>,greater<long long>> pq;
        while(!q.empty()){
            int n = q.size();
            long long sum = 0;
            for(int i = 0;i < n;i++){
                TreeNode* qFront = q.front();
                q.pop();
                sum += qFront->val;
                if(qFront->left) q.push(qFront->left);
                if(qFront->right) q.push(qFront->right);
            }
            pq.push(sum);
            if(pq.size() > k) pq.pop();
        }
        if(pq.size() == k) return pq.top();
        return -1;
    }
};