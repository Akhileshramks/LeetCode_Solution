class Solution {
public:
    int minCostClimbingStairs(vector<int>& costs) {
        int n = costs.size();
        vector<int> dp(n+1,1e8);
        dp[0] = costs[0];
        dp[1] = costs[1];
        for(int step = 2;step<n;step++){
            dp[step] = min(dp[step-1],dp[step-2])+costs[step];
        }
        return min(dp[n-1],dp[n-2]);
    }
};