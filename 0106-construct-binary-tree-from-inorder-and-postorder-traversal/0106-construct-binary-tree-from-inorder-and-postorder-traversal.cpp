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
    void helper(vector<int>& inorder,unordered_map<int,int>& inMap){
        int n = inorder.size();
        for(int i = 0;i < n;i++){
            inMap[inorder[i]] = i;
        }
    }
    TreeNode* build(vector<int>& inorder,int is,int ie,vector<int>& postorder,int ps,int pe,unordered_map<int,int>& inMap){
        if(is > ie || ps > pe) return NULL;
        TreeNode* root = new TreeNode(postorder[pe]);
        int ind = inMap[postorder[pe]];
        root->left = build(inorder,is,ind-1,postorder,ps,ps+ind-is-1,inMap);
        root->right = build(inorder,ind+1,ie,postorder,ps+ind-is,pe-1,inMap);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int,int> inMap;
        helper(inorder,inMap);
        int n = inorder.size();
        int m = inorder.size();
        if(n!=m) return NULL;
        return build(inorder,0,n-1,postorder,0,n-1,inMap);
    }
};