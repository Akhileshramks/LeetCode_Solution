class Solution {
public:
    int pickUp(vector<vector<int>>& grid, int i, int j1, int j2, int n,int m,vector<vector<vector<int>>>& dp){
        if(j1 < 0 || j2 < 0 || i < 0 || j1 >= m || j2 >= m || i >= n) return -1;
        if(dp[i][j1][j2] != -1) return dp[i][j1][j2];
        int nextStep = 0;
        int dy[3] = {-1,0,1};
        int currStep = j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2];
        for(int dy1 : dy){
            for(int dy2 : dy){
                nextStep = max(nextStep, pickUp(grid, i+1, j1+dy1, j2+dy2, n, m, dp));
            }
        }
        return dp[i][j1][j2] = nextStep + currStep;
    }
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<int>>>dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
        return pickUp(grid,0,0,m-1,n,m,dp);
    }
};