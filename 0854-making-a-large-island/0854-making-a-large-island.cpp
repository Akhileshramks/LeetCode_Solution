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
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        vector<pair<int,int>> coordinates = {{0,1},{1,0},{-1,0},{0,-1}};
        Disjoint graph(n*m);
        int maxi =0;
        for(int i = 0;i<n;i++){
            for(int j =0;j<m;j++){
                if(grid[i][j]){
                    for(auto [dx,dy] : coordinates){
                        int xx = i+dx;
                        int yy = j+dy;
                        if(xx>=0 && xx<n && yy>=0 && yy<m && grid[xx][yy]){
                            graph.unionfind(n*i+j,n*xx+yy);
                        }
                    }
                }
            }
        }
        for(int i = 0;i<n;i++){
            for(int j =0;j<m;j++){
                if(grid[i][j] == 0){
                    unordered_set<int> st;
                    int island = 1;
                    for(auto [dx,dy] : coordinates){
                        int xx = i+dx;
                        int yy = j+dy;
                        if(xx>=0 && xx<n && yy>=0 && yy<m && grid[xx][yy]){
                            int up_u = graph.find(n*xx+yy);
                            st.insert(up_u);
                        }
                    }
                    for(int i : st){
                        island+=graph.size[i];
                    }
                    maxi = max(maxi,island);
                }

            }
        }
        if(maxi == 0) return *max_element(graph.size.begin(),graph.size.end());
        return maxi;
    }
};