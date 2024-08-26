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
        vector<vector<int>> dp(m+1,vector<int>(n+1,-1));
        return wildcardmatching(m-1,n-1,s,p,dp);
    }
};