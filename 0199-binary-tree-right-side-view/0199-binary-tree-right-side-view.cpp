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
    map<int,int> rightView;
    void rightSide(TreeNode* root,int level){
        if(root == nullptr) return;
        rightView[level] = root->val;
        rightSide(root->left,level+1);
        rightSide(root->right,level+1);
    }

    vector<int> rightSideView(TreeNode* root) {
        rightSide(root,0);
        vector<int> result;
        for(auto i : rightView){
            result.push_back(i.second);
        }
        return result;
    }
};