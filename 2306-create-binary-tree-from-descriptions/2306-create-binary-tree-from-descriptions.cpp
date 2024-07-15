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
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int,TreeNode*> mp;
        unordered_map<int,bool> r;
        for(auto i : descriptions){
            TreeNode* node = mp[i[0]] ? mp[i[0]] : (mp[i[0]] = new TreeNode(i[0]));
            TreeNode* child = mp[i[1]] ? mp[i[1]] : (mp[i[1]] = new TreeNode(i[1]));
            r[i[1]] = true;
            if(i[2] == 0) node->right = child;
            else node->left = child;
        }
        for (const auto& i : mp) {
            if(!r[i.first]){
                return mp[i.first];
            }
        }
        return NULL;
    }
};