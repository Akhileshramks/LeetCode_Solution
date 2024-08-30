class Disjoint{
    public:
        vector<int> rank,parent;
        Disjoint(int n){
            parent.resize(n+1);
            rank.resize(n+1,0);
            for(int i= 0;i<=n;i++){
                parent[i] = i;
            }
        }

        int findparent(int s){
            if(parent[s] == s) return s;
            return parent[s] = findparent(parent[s]);
        }

        void unionset(int x,int y){
            int up_x = findparent(x);
            int up_y = findparent(y);
            if( up_x == up_y){
                return;
            }
            else if(rank[up_x] > rank[up_y]){
                parent[up_y] = up_x;
            }
            else if(rank[up_x] < rank[up_y]){
                parent[up_x] = up_y;
            }
            else{
                parent[up_x] = up_y;
                rank[up_y]++;
            }
            return;
        }
};
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        Disjoint dsu(n);
        int provinces = n;
        for(int i = 0;i < n;i++){
            for(int j = 0;j<n;j++){
                if(isConnected[i][j] && dsu.findparent(i) != dsu.findparent(j)){
                    dsu.unionset(i,j);
                    provinces -- ;
                }
            }
        }
        return provinces;
    }
};