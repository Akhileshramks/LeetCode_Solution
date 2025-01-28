class Solution {
public:
    int ans = 0;
    int dfs(int i,int j,vector<vector<int>>& grid,vector<vector<int>>& visited){
        int res = grid[i][j];
        visited[i][j] = true;
        int m = grid.size();
        int n = grid[0].size();
        int x[] = {-1,0,1,0};
        int y[] = {0,1,0,-1};
        for(int k = 0;k < 4;k++){
            int dx = i + x[k];
            int dy = j + y[k];
            if(dx >= 0 && dx < m && dy >= 0 && dy < n && grid[dx][dy] > 0 && !visited[dx][dy]){
                res += dfs(dx,dy,grid,visited);
            }
        }
        return res;
    }
    int findMaxFish(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> visited(m,vector<int>(n,0));
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                if(grid[i][j] >0 && !visited[i][j]){
                    ans = max(ans,dfs(i,j,grid,visited));
                }
            }
        }
        return ans;
    }
};