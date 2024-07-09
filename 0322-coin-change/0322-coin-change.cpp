class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int m = coins.size();
        vector<int> dp(amount + 1, 1e6); 
        dp[0]=0;
        for(int i=0;i<m;i++){
            int coin = coins[i];
            for(int j =coin;j<amount+1;j++){
                    dp[j] = min(dp[j],1+dp[j-coin]);
                }
        }
        return dp[amount]>=1e6 ? -1 : dp[amount];
    }
};