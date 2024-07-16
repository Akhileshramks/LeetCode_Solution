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
    // Helper function to find the path from the root to the target node
    bool dfs(TreeNode* root, int target, string& path) {
        if (root == nullptr) return false;

        if (root->val == target) return true;

        path.push_back('L');
        if (dfs(root->left, target, path)) return true;
        path.pop_back();

        path.push_back('R');
        if (dfs(root->right, target, path)) return true;
        path.pop_back();

        return false;
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        string path_start, path_dest;
        
        // Find path from root to startValue
        dfs(root, startValue, path_start);
        
        // Find path from root to destValue
        dfs(root, destValue, path_dest);

        int m = path_start.size();
        int n = path_dest.size();

        // Find the first point where paths diverge
        int i = 0;
        while (i < m && i < n && path_start[i] == path_dest[i]) {
            i++;
        }

        // Create the result path: 'U' for steps up to the LCA, then the remaining path to the destination
        string result = string(m - i, 'U') + path_dest.substr(i);
        return result;
    }
};