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
        vector<int> prev(n,0);
        vector<int> curr(n,0);
        for(int m1=0;m1<m;m1++){
            for(int n1=0;n1<n;n1++){
                if(m1 ==0 && n1 ==0 ){
                    curr[0] = 1;
                    continue;
                } 
                int up =  (m1>0) ? prev[n1]: 0;
                int left =  (n1>0) ? curr[n1-1] : 0;
                curr[n1]=up+left;
            }
            prev = curr;
        }
        return prev[n-1];
    }
};