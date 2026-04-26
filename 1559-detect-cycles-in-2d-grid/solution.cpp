class Solution {
public:
    bool isCycleDetect(vector<vector<char>>& grid, vector<vector<int>>& visited, int src_i, int src_j, int par_i, int par_j, int n, int m){
        int dx[] = {-1, 0, 0, 1};
        int dy[] = {0, -1, 1, 0};
        visited[src_i][src_j] = true;
        for(int i = 0;i < 4;i++){
            int x = src_i + dx[i];
            int y = src_j + dy[i];
            if(x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != grid[src_i][src_j] || (par_i == x && par_j == y)) continue;
            if(visited[x][y]) return true;
            if(isCycleDetect(grid, visited, x, y, src_i, src_j, n, m)) return true;
        }
        return false;
    }
    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m, false));
        bool cycle = false;
        for(int i = 0;i < n;i++){
            for(int j = 0;j <m;j++){
                if(!visited[i][j]){
                    bool isCycle = isCycleDetect(grid, visited, i, j, -1, -1, n, m);
                    if(isCycle) return isCycle;
                }
            }
        }
        return false;
    }
};