class UnionFind{
    public:
        vector<int> parent;
        vector<int> size;

        UnionFind(int n){
            parent.resize(n);
            size.resize(n);
            for(int i = 0;i < n;i++){
                parent[i] = i;
                size[i] = 1;
            }
        }

        int findParent(int i){
            if(parent[i] == i) return i;
            return parent[i] = findParent(parent[i]);
        }

        void merge(int i, int j){
            int ul_i = findParent(i);
            int ul_j = findParent(j);
            if(ul_i == ul_j) return;
            if(size[ul_i] >= size[ul_j]){
                parent[ul_j] = ul_i;
                size[ul_i] += size[ul_j]; 
            }else{
                parent[ul_i] = ul_j;
                size[ul_j] += size[ul_i]; 
            }
            return;
        }
};
class Solution {
public:
    int convert2dtod(int i, int j, int m){
        return i * m + j;
    }
    bool isValid(int i, int j, int n, int m){
        return (i >= 0 && i < n && j >= 0 && j < m);
    }
    bool hasValidPath(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        UnionFind graph(n*m);
        vector<int> state = {0, 0b1010, 0b0101, 0b1100, 0b0110, 0b1001, 0b0011};
        vector<pair<int,int>> steps = {{-1,0}, {0,1}, {1, 0}, {0,-1}};
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                for(int k = 0;k < 4;k++){
                    int dx = i + steps[k].first;
                    int dy = j + steps[k].second;
                    int currState = state[grid[i][j]];
                    if(isValid(dx, dy, n, m)){
                        int nextState = state[grid[dx][dy]];
                        int currRoad = currState & (1 << k);
                        int nextRoad = nextState & (1 << ((k + 2) % 4));
                        if(currRoad && nextRoad) graph.merge(convert2dtod(i, j, m), convert2dtod(dx, dy, m));
                    }
                }
            }
        }

        return graph.findParent(convert2dtod(0, 0, m)) == graph.findParent(convert2dtod(n - 1, m - 1, m));
    }
};