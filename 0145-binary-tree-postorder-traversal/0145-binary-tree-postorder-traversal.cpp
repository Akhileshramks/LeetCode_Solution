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
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> ans;
        TreeNode* previousNode = nullptr;
        while(!st.empty() || root != nullptr){
            if(root != nullptr){
                st.push(root);
                root = root->left;
            }
            else{
                root = st.top();
                if(root->right == nullptr || root->right == previousNode){
                    ans.push_back(root->val);
                    previousNode = root;
                    st.pop();
                    root = nullptr;
                }else{
                    root = root->right;
                }
            }
        }
        return ans;
    }
};