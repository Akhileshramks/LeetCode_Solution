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
    set<int> to_delete_set;
    TreeNode* deleteNode(TreeNode* root,vector<TreeNode*>& res,bool is_root){
        if(root == NULL) return NULL;
        bool is_delete = to_delete_set.find(root->val) != to_delete_set.end();
        if(is_root && !is_delete) res.push_back(root);
        root->left = deleteNode(root->left,res,is_delete);
        root->right = deleteNode(root->right,res,is_delete);
        if(is_delete) return NULL;
        return root;
    }
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> res;
        for(int i : to_delete){
            to_delete_set.insert(i);
        }
        deleteNode(root,res,true);
        return res;
    }
};