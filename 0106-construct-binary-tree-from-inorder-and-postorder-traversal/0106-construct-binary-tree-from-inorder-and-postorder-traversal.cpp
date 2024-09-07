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
    TreeNode* treeBuild(vector<int>& inorder, vector<int>& postorder,int is, int ie, int ps, int pe,unordered_map<int,int>& ind){
        if(is>ie || ps>pe) return NULL;
        TreeNode* root = new TreeNode(postorder[pe]);
        int curr_ind = ind[postorder[pe]];
        int n = curr_ind - is;
        root -> left = treeBuild(inorder,postorder,is,curr_ind-1,ps,ps+n-1,ind);
        root -> right = treeBuild(inorder,postorder,curr_ind+1,ie,ps+n,pe-1,ind);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int,int> ind;
        if(inorder.size() != postorder.size()) return NULL;
        int n = inorder.size();
        for(int i = 0;i < n;i++) ind[inorder[i]] = i;
        return treeBuild(inorder,postorder,0,n-1,0,n-1,ind);
    }
};