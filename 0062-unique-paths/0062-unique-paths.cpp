class Solution {
public:
    int path(int m1,int n1,int m,int n, vector<vector<int>>& dp){
        if(m1 == 0 && n1 == 0) return 1;
        
        if(m1<0 || n1<0) return 0;
        if(dp[m1][n1]!=-1) return dp[m1][n1];
        int up = (m1>0) ? path(m1-1,n1,m,n,dp) : 0;
        int left = (n1>0) ? path(m1,n1-1,m,n,dp) : 0;
        return dp[m1][n1]=up+left;
    }
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n,-1));
        return path(m-1,n-1,m,n,dp);
    }
};