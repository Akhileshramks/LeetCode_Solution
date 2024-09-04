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
    vector<int> preOrder;
    vector<int> preorderTraversal1(TreeNode* root) {
        if(root == NULL) return {};
        preOrder.push_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
        return preOrder;
    }
    vector<int> preorderTraversal(TreeNode* root) {
        if(root == NULL) return {};
        stack<TreeNode*> st;
        st.push(root);
        while(!st.empty()){
            TreeNode* node = st.top();
            st.pop();
            preOrder.push_back(node->val);
            if(node->right) st.push(node->right);
            if(node->left) st.push(node->left);
        }
        return preOrder;
    }
};