class Disjoint{
    public:
        vector<int> parent;
        vector<int> rank;
        Disjoint(int n){
            parent.resize(n+1);
            rank.resize(n+1,0);
            for(int i=0;i<=n;i++){
                parent[i] = i;
            }
        }

        int find(int u){
            if(parent[u] == u) return u;
            return parent[u] = find(parent[u]);
        }

        void union_find(int u,int v){
            int up_u = find(u);
            int up_v = find(v);
            if(up_u == up_v) return ;
            if(rank[up_u] > rank[up_v]){
                parent[up_v] = up_u;
            }
            else if(rank[up_v] > rank[up_u]){
                parent[up_u] = up_v;
            }
            else{
                parent[up_u] = up_v;
                rank[up_v]++;
            }
        }
};
class Solution {
public:

    int makeConnected(int n, vector<vector<int>>& connections) {
        Disjoint graph(n);
        int g = connections.size();
        int m = 0;
        for(auto i : connections){
            if(graph.find(i[0]) != graph.find(i[1])){
                graph.union_find(i[0],i[1]);
            }
        }
        for(int i = 0; i < n;i++){
            if(graph.find(i) == i) m++;
        }
        if(n-1 > g) return -1;
        return m-1;
    }
};