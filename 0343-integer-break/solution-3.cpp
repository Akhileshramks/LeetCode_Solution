class Solution {
public:
    int integerBreak(int n) {
        // vector<int> dp(n+1, 0);
        // dp[1] = 1;
        // for(int i = 2;i <= n;i++){
        //     for(int j = 1;j < i;j++){
        //         dp[i] = max(dp[i], max(dp[i-j] * j, j * (i-j)));
        //     }
        // }
        // return dp[n];

        // When n > 4, the number 3 gives the highest product
        int product = 1;
        if(n == 1) return 1;
        else if(n < 4) return n-1;
        else if(n == 4) return 4;
        while(n > 4){
            n-=3;
            product *= 3;
        }
        return product * n;
    }
};