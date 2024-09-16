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
    TreeNode* constructBST(vector<int>& preorder,vector<int>& inorder,int preStart,int preEnd,int inStart,int inEnd,unordered_map<int,int> &order){
        if(preStart > preEnd || inStart > inEnd) return NULL;
        TreeNode* root = new TreeNode(preorder[preStart]);
        int ind = order[preorder[preStart]];
        int n = ind - inStart;
        root->left = constructBST(preorder,inorder,preStart+1,preStart+n,inStart,ind-1,order);
        root->right = constructBST(preorder,inorder,preStart+n+1,preEnd,ind+1,inEnd,order);
        return root;

    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        vector<int> inorder(preorder.begin(),preorder.end());
        sort(inorder.begin(),inorder.end());
        int n = preorder.size();
        unordered_map<int,int> order;
        for(int i = 0;i<n;i++) order[inorder[i]] = i;
        return constructBST(preorder,inorder,0,n-1,0,n-1,order);
    }
};