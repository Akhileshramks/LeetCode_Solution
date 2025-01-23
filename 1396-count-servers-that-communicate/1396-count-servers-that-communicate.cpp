class UnionFind{
    public:
    vector<int> parent,rank;
    UnionFind(int n){
        parent.resize(n);
        rank.resize(n);
        for(int i = 0;i < n;i++){
            parent[i] = i;
        }
    }
    int findparent(int u){
        if(parent[u] == u){
            return u;
        }
        return parent[u] = findparent(parent[u]);
    }
    void union_set(int u,int v){
        int parent_u = findparent(u);
        int parent_v = findparent(v);
        if(parent_u == parent_v) return;
        else if(rank[parent_u] < rank[parent_v]){
            parent[parent_u] = parent_v;
            rank[parent_v]++;
        }
        else{
            parent[parent_v] = parent_u;
            rank[parent_u]++;
        }
    }
};
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int last;
        UnionFind graph(m*n);
        for(int i = 0; i < m;i++){
            last = -1;
            for(int j = 0;j < n;j++){
                if(grid[i][j] == 1){
                    if(last != -1) graph.union_set(i*n+j,i*n+last);
                    last = j;
                }
            }
        }
        for(int j = 0; j < n;j++){
            last = -1;
            for(int i = 0;i < m;i++){
                if(grid[i][j] == 1){
                    if(last != -1) graph.union_set(i*n+j,last*n+j);
                    last = i;
                }
            }
        }
        int res = 0;
        unordered_map<int,int> noOfComponents;
        for(int i = 0;i < m*n;i++){
            if(grid[i/n][i%n]) noOfComponents[graph.findparent(i)]++;
        }
        for(int i = 0;i < m*n;i++){
            if(noOfComponents[i] > 1) res += noOfComponents[i];
        }
        return res;
    }
};