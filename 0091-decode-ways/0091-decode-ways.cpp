class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n+2,0);
        dp[0] = 1;
        dp[1] = 1;
        if(s[0] == '0') return 0;
        for(int i=0;i<n;i++){
            if(s[i]-'0' != 0){
                dp[i+2] += dp[i+1];
            }
            int m = i-1 >= 0 ?  (s[i-1]-'0')*10 + s[i]-'0' :27;
            if(m>=10 && m<=26){
                dp[i+2] += dp[i];
            }
        }
        return dp[n+1];
    }
};