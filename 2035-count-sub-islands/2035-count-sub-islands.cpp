class Solution {
public:
    bool countIsland(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int i, int j, int n, int m, vector<vector<bool>>& visited) {
        if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || grid2[i][j] == 0)
            return true;

        visited[i][j] = true;
        bool isSubIsland = grid1[i][j] == 1;
        
        isSubIsland &= countIsland(grid1, grid2, i-1, j, n, m, visited);
        isSubIsland &= countIsland(grid1, grid2, i+1, j, n, m, visited);
        isSubIsland &= countIsland(grid1, grid2, i, j-1, n, m, visited);
        isSubIsland &= countIsland(grid1, grid2, i, j+1, n, m, visited);

        return isSubIsland;
    }

    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int n = grid1.size();
        int m = grid1[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int count = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid2[i][j] == 1) {
                    if (countIsland(grid1, grid2, i, j, n, m, visited)) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};
