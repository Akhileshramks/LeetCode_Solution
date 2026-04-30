class Solution {
public:
    pair<int,int> findCostScore(int i){
        if(i == 0) return {0, 0};
        else if(i == 1) return {1,1};
        else return {1,2};
    }
    int findMaxPath(vector<vector<int>>& grid, int i, int j, int cost, int k, int n, int m, vector<vector<vector<int>>>& dp){
            if(i == n - 1 && j == m - 1){
                pair<int,int> new_cs = findCostScore(grid[i][j]);
                if(cost + new_cs.first <= k) return new_cs.second;
                else return -1;
            }
            pair<int,int> curr_cs = findCostScore(grid[i][j]);
            if(cost + curr_cs.first > k) return -1;
            if(dp[i][j][cost] != -2) return dp[i][j][cost];
            int next_score = -1;
            vector<vector<int>> nextState = {{1, 0}, {0, 1}};
            for(int r = 0;r < 2;r++){
                int next_i = i + nextState[r][0], next_j = j + nextState[r][1];
                if(next_i >= 0 && next_i < n && next_j >= 0 && next_j < m){
                    next_score = max(next_score, findMaxPath(grid, next_i, next_j, cost + curr_cs.first, k, n, m, dp));
                }
            }
            return dp[i][j][cost] = next_score != -1 ? next_score + curr_cs.second :  -1;
    }
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        int ans = -1;

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k+1, -1)));

        for(int cost = 0; cost <= k; cost++){
            auto [c, s] = findCostScore(grid[n-1][m-1]);
            if(cost + c <= k) dp[n-1][m-1][cost] = s;
        }

        for(int i = n - 1;i >= 0;i--){
            for(int j = m - 1;j >= 0;j--){
                if(i == n - 1 && j == m - 1) continue;
                for(int cost = 0;cost <= k;cost++){
                    pair<int,int> curr_cs = findCostScore(grid[i][j]);
                    if(cost + curr_cs.first > k) continue;
                    int next_score = -1;
                    if(i + 1 < n && dp[i + 1][j][cost + curr_cs.first] != -1) next_score = max(next_score, dp[i + 1][j][cost + curr_cs.first]);
                    if(j + 1 < m && dp[i][j + 1][cost + curr_cs.first] != -1) next_score = max(next_score, dp[i][j + 1][cost + curr_cs.first]);
                    dp[i][j][cost] = next_score != -1 ? next_score + curr_cs.second :  -1;
                }
            }
        }
        for(int c = 0;c <= k; c++) ans = max(ans, dp[0][0][c]);
        return ans;
    }
};