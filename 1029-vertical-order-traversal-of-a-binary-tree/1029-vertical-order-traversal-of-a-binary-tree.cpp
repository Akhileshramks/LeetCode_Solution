class Solution {
public:
    map<int,map<int,multiset<int>>> m;
    vector<vector<int>> res;
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        queue<pair<TreeNode *,pair<int,int>>> q;
        q.push({root,{0,0}});
        pair<TreeNode *,pair<int,int>> p;
        while(!q.empty()){
            p = q.front();
            q.pop();
            m[p.second.second][p.second.first].insert(p.first->val);
            if(p.first->left) q.push({p.first->left,{p.second.first+1,p.second.second-1}});
            if(p.first->right) q.push({p.first->right,{p.second.first+1,p.second.second+1}});
        }
        for(auto i:m){
            vector<int> v;
            for(auto j : i.second){
                v.insert(v.end(),j.second.begin(),j.second.end());
            }
            res.push_back(v);
        }
        return res;
    }
};