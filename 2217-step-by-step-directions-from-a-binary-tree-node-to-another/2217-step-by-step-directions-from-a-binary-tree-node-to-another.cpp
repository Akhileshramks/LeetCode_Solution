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
    bool dfs(TreeNode* root,int target,string& dest){
        if(root == nullptr) return false;

        if(root->val == target) return true;

        dest.push_back('L');
        if(dfs(root->left,target,dest)) return true;
        dest.pop_back();

        dest.push_back('R');
        if(dfs(root->right,target,dest)) return true;
        dest.pop_back();

        return false;
    }
    string getDirections(TreeNode* root, int startValue, int destValue) {
        string path_start,path_dest;
        dfs(root,startValue,path_start);
        dfs(root,destValue,path_dest);

        int m = path_start.size();
        int n = path_dest.size();

        int mini = min(m,n);
        int i;
        for(i = 0;i<mini;i++){
            if(path_start[i] != path_dest[i]) break;
        }

        string ans = string(m-i,'U') + string(path_dest.begin()+i,path_dest.end());
        return ans;
    }
};