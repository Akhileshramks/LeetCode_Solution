class Solution {
public:
    bool Palindrome(int i, int j, string &s) {
        while (i < j) {
            if (s[i] != s[j]) return false;
            i++;
            j--;
        }
        return true;
    }
    int mincutpalindrome(int i,int n,string s,vector<int> &dp){
        if(i>=n) return 0;
        if(dp[i]!=-1) return dp[i];
        int mini = INT_MAX;
        for(int k=i;k<n;k++){
            if(Palindrome(i,k,s)) {
                int ans =  mincutpalindrome(k+1,n,s,dp)+1;
                mini = min(mini,ans);
            }
        }
        return dp[i] = mini;
    }
    int minCut(string s) {
        int n = s.size();
        //vector<vector<int>> dp(n,vector<int>(n,-1));
        vector<int> dp(n+1,0);
        
        for(int i=n-1;i>=0;i--){
            int mini = INT_MAX;
            for(int k=i;k<n;k++){
                if(Palindrome(i,k,s)) {
                    int ans =  dp[k+1]+1;
                    mini = min(mini,ans);
                }
            }
            dp[i] = mini;
        }
        return dp[0]-1;
        //return mincutpalindrome(0,n,s,dp)-1;
    }
};