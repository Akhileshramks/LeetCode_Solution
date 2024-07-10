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
    vector<int> m;
    vector<int> rightside(TreeNode* root,int level){
        if(root!=NULL){
            if(m.size() == level) m.push_back(root->val);
            if(root->right) rightside(root->right,level+1);
            if(root->left) rightside(root->left,level+1);
        }
        return m;
    }
    vector<int> rightSideView(TreeNode* root) {
        return rightside(root,0);
    }
};