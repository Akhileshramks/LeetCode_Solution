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
    int ans = 0;
    vector<int> goodPair(TreeNode* root,int distance){
        if(root == NULL) return {};
        if(root->left == NULL && root->right== NULL) return {1};
        vector<int> left = goodPair(root->left, distance);
        vector<int> right = goodPair(root->right, distance);
         for (int l : left) 
            for (int r : right) 
                if (l + r <= distance) ans++;
        vector<int> combined;
        for (int i : left) {
            if (i + 1 < distance) combined.push_back(i + 1);
        }
        for (int i : right) {
            if (i + 1 < distance) combined.push_back(i + 1);
        }
        return combined;
    }
    int countPairs(TreeNode* root, int distance) {
        goodPair(root,distance);
        return ans;
    }
};