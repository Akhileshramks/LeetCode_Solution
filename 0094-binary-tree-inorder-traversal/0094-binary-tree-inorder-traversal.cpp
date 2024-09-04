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
    vector<int> inorderTraversal(TreeNode* root) {
        if(!root) return {};
        stack<TreeNode*> st;
        vector<int> inOrder;
        TreeNode* current = root;
        while(!st.empty() || current){
            while(current){
                st.push(current);
                current = current -> left;
            }
            current = st.top();
            st.pop();
            inOrder.push_back(current->val);
            current = current->right;
        }
        return inOrder;
    }
};