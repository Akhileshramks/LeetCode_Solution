class UnionFind{
    public:
        vector<int> parent,rank;
        UnionFind(int n){
            parent.resize(n);
            rank.resize(n);
            for(int i = 0;i < n; i++){
                parent[i] = i;
            }
        }
        int findParent(int u){
            if(parent[u] == u) return u;
            return parent[u] = findParent(parent[u]);
        }
        void unionNode(int u,int v){
            int parent_u = findParent(u);
            int parent_v = findParent(v);
            if (parent_u == parent_v) return;
            else if(rank[parent_u] > rank[parent_v]){
                parent[parent_v] = parent_u;
                rank[parent_v]++;
            }
            else{
                parent[parent_u] = parent_v;
                rank[parent_u]++;
            }
        }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UnionFind graph(n);
        for(int i = 0;i < n;i++){
            int u = edges[i][0]-1;
            int v = edges[i][1]-1;
            if(graph.findParent(u) == graph.findParent(v)){
                return {u+1,v+1};
            }
            else{
                graph.unionNode(u,v);
            }
        }
        return {};
    }
};