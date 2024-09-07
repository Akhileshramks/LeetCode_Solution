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
    TreeNode* treeBuild(vector<int>&preorder,vector<int>& inorder,int ps,int pe,int is,int ie,unordered_map<int,int> &ind){
        if(ps>pe || is>ie) return NULL;
        TreeNode* root = new TreeNode(preorder[ps]);
        int curr_ind = ind[preorder[ps]];
        int n = curr_ind - is;
        root->left = treeBuild(preorder,inorder,ps+1,ps+n,is,curr_ind-1,ind);
        root->right = treeBuild(preorder,inorder,ps+n+1,pe,curr_ind+1,ie,ind);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int,int> ind;
        if(inorder.size() != preorder.size()) return NULL;
        int n = inorder.size();
        for(int i= 0;i<n;i++) ind[inorder[i]] = i;
        return treeBuild(preorder,inorder,0,n-1,0,n-1,ind);
    }
};