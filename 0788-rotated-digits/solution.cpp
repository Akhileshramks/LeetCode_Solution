class Solution {
public:
    vector<int> isValid = {1, 1, 1, 0, 0, 1, 1, 0, 1, 1};
    int findDigitSum(int ind, int tight, string s, int isPresent, vector<vector<vector<int>>>& dp){
        if(ind == s.size()){
            if(!isPresent) return 0;
            return 1;
        }
        if(dp[ind][tight][isPresent] != -1) return dp[ind][tight][isPresent];
        int limit = tight ? s[ind] - '0' : 9;
        int ans = 0;
        for(int i = 0;i <= limit;i++){
            if(!isValid[i]) continue;
            int new_isPresent = isPresent | (i == 2 || i == 5 || i == 6 || i == 9);
            int new_tight = (tight & (s[ind] - '0' == i)) ? tight : 0;
            ans += findDigitSum(ind + 1, new_tight, s, new_isPresent, dp);
        }
        return dp[ind][tight][isPresent] = ans;
    }
    int rotatedDigits(int n) {
        string s = to_string(n);
        vector<vector<vector<int>>> dp(s.size() , vector<vector<int>>(2, vector<int>(2, -1)));
        return findDigitSum(0, 1, s, 0, dp);
    }
};