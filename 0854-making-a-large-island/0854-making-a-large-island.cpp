class DisjointSet{
    public:
        vector<int> parent;
        vector<int> size;

        DisjointSet(int n){
            parent.resize(n);
            size.resize(n,1);
            for(int i = 0;i < n;i++){
                parent[i] = i;
            }
        }

        int find(int u){
            if(parent[u] == u) return u;
            return parent[u] = find(parent[u]);
        }

        void unionSet(int u,int v){
            int parent_u = find(u);
            int parent_v = find(v);
            if(parent_u == parent_v) return;
            else if(size[parent_u] > size[parent_v]){
                parent[parent_v] = parent_u;
                size[parent_u] += size[parent_v];
            }
            else{
                parent[parent_u] = parent_v;
                size[parent_v] += size[parent_u];
            }
        }

};
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int total = m*n;
        DisjointSet graph(total);
        int x[] = {0,1,0,-1};
        int y[] = {1,0,-1,0};
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                if(grid[i][j] == 1){
                    for(int k = 0;k < 4;k++){
                        int dx = i + x[k];
                        int dy = j + y[k];
                        if(dx >= 0 && dx < m && dy >=0 && dy < n && grid[dx][dy]){
                            graph.unionSet(dx*n+dy,i*n+j);
                        }
                    }

                }
            }
        }
        int maxi = 0;
        for(int i = 0;i < total;i++) maxi = max(maxi,graph.size[i]);
        for(int i =0;i < m;i++){
            for(int j = 0;j < n;j++){
                if(grid[i][j] == 0){
                    unordered_set<int> st;
                    for(int k = 0;k < 4;k++){
                        int dx = i + x[k];
                        int dy = j + y[k];
                        if(dx >= 0 && dx < m && dy >=0 && dy <n && grid[dx][dy]){
                            st.insert(graph.find(dx*m+dy));
                        }
                    }
                    int res = 1;
                    for(int p : st) res += graph.size[p];
                    maxi = max(maxi,res);
                }
            }
        }
        return maxi;
    }
};