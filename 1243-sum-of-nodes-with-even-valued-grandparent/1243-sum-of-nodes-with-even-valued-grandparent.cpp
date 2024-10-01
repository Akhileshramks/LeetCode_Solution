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
    int sum = 0;
    void sumEvenGP(TreeNode* root,bool flag){
        if(root == NULL) return;
        int leftChild = (root->left == NULL) ? 0 : root->left->val;
        int rightChild = (root->right == NULL) ? 0 : root->right->val;
        if(flag == true){
            sum += (leftChild+rightChild);
        }
        bool next = root->val % 2 == 0;
        sumEvenGP(root->left,next);
        sumEvenGP(root->right,next);
        return;
    }
    int sumEvenGrandparent(TreeNode* root) {
        sumEvenGP(root,false);
        return sum;
    }
};