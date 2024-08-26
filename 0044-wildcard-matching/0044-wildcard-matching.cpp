class Solution {
public:
    bool wildcardmatching(int i,int j,string& s, string& p,vector<vector<int>> &dp){
        if(i<0 && j<0) return true;
        else if(i<0){
            for(int m = 0;m<=j;m++){
                if(p[m]!='*'){
                    return false;
                }
            }
            return true;
        }
        else if(j<0) return false;
        if(dp[i][j]!=-1) return dp[i][j];
        if(s[i] == p[j] || p[j] == '?'){
            return dp[i][j] = wildcardmatching(i-1,j-1,s,p,dp);
        }
        else if(p[j]=='*'){
            return dp[i][j] = wildcardmatching(i-1,j,s,p,dp) || wildcardmatching(i,j-1,s,p,dp) || wildcardmatching(i-1,j-1,s,p,dp) ;
        }
        else return dp[i][j] = false;

    }
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
        //return wildcardmatching(m-1,n-1,s,p,dp);

        //Tabulation 

        dp[0][0] = true;
        bool flag = true;
        for(int j = 1;j<=n;j++){
            if(p[j-1]!='*' && flag) flag = false;
            dp[0][j] = flag;
        }

        for(int i =1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(s[i-1] == p[j-1] || p[j-1] == '?'){
                    dp[i][j] = dp[i-1][j-1];
                }
                else if(p[j-1]=='*'){
                    dp[i][j] = dp[i-1][j] || dp[i][j-1]  ;
                }
                else dp[i][j] = false;
            }
        }

        return dp[m][n];
    }
};