class Disjoint{
    public:
        vector<int> parent;
        vector<int> size;

        Disjoint(int n){
            parent.resize(n+1);
            size.resize(n+1,1);
            for(int i=0;i<=n;i++){
                parent[i] = i;
            }
        }

        int find(int u){
            if(parent[u] == u) return u;
            return parent[u] = find(parent[u]);
        }

        void unionfind(int u,int v){
            int up_u = find(u);
            int up_v = find(v);
            if(up_u == up_v) return;
            else if(size[up_u] > size[up_v]){
                parent[up_v] = up_u;
                size[up_u]+=size[up_v];
            }
            else{
                parent[up_u] = up_v;
                size[up_v]+=size[up_u];
            }
            return;
        }
};
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        Disjoint graph(n);
        unordered_map<string,int> mpp;
        unordered_map<int,string> names;
        for(int i =0;i<n;i++){
            names[i] = accounts[i][0];
            for(int j=1;j<accounts[i].size();j++){
                if(mpp.find(accounts[i][j]) == mpp.end()){
                    mpp[accounts[i][j]] = i;
                }
                else{
                    graph.unionfind(i,mpp[accounts[i][j]]);
                }
                
            }
        }
        map<int,vector<string>> result;
        for(auto i : mpp){
            int ul_p = graph.find(i.second);
            result[ul_p].push_back(i.first);
        }
        vector<vector<string>> res;
        for(auto [ind,emails] : result){
            vector<string> r;
            r.push_back(names[ind]);
            sort(emails.begin(),emails.end());
            r.insert(r.end(),emails.begin(),emails.end());
            res.push_back(r);
        }
        return res;
    }
};