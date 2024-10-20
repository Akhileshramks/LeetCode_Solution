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
        
        
        vector<vector<int>> res;
        if(root == NULL) return res;
        queue<TreeNode*> q;
        q.push(root);
        int zigzagFlag = false;
        while(!q.empty()){
            int noOfNodes = q.size();
            vector<int> levelOrder(noOfNodes);
            for(int i = 0;i < noOfNodes;i++){
                TreeNode* node = q.front();
                q.pop();
                int ind = zigzagFlag ? noOfNodes-1-i : i;
                levelOrder[ind] = node->val;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            zigzagFlag = !zigzagFlag;
            res.push_back(levelOrder);
        }
        return res;
    }
};