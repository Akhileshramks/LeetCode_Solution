class Solution {
public:
    int countPossible(vector<int> coins, int ind, int amount, vector<vector<int>>& dp){
        if(ind == 0) return amount % coins[ind] == 0;
        if(ind < 0) return 0;
        if(dp[ind][amount] != -1) return dp[ind][amount];
        int notTake = countPossible(coins, ind - 1, amount, dp);
        int take = 0;
        if(coins[ind] <= amount){
            take = countPossible(coins, ind, amount - coins[ind], dp);
        }
        return dp[ind][amount] = take + notTake;
    }
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<long long> prev(amount+1, 0);
        for(int i = 0;i <= amount;i++) prev[i] = (i % coins[0] == 0);
        for(int ind = 1;ind < n;ind++){
            vector<long long> curr(amount+1, 0);
            for(int remaining = 0; remaining <= amount;remaining++){
                int notTake = prev[remaining];
                int take = 0;
                if(coins[ind] <= remaining){
                    take = (curr[remaining - coins[ind]]);
                }
                curr[remaining] = (1ll*take + notTake);
            }
            prev = curr;
        }
        return prev[amount];
    }
};