class Solution {
public:
    int MOD = 1e9 + 7;
    string subtrackOne(string s){
        if(s == "0") return s;
        int n = s.size();
        int i = n - 1;
        while(i >= 0 && s[i] == '0'){
            s[i] = '9';
            i--;
        }
        if(i >= 0) s[i]--;

        if(s[0] == '0' && s.size() > 1){
            s = s.substr(1);
        }
        return s;
    }
    long long countDigitSum(string s, int ind, int tight, int sum, int minSum, int maxSum, vector<vector<vector<long long>>>& dp){
        if(sum > maxSum) return 0;
        if(ind == s.size()){
            if(sum >= minSum && sum <= maxSum) return 1;
            return 0;
        }
        if(dp[ind][tight][sum] != -1) return dp[ind][tight][sum];
        int limit = tight ? s[ind] - '0' : 9;
        long long res = 0;
        for(int i = 0;i <= limit; i++){
            int new_tight = (tight & (s[ind] - '0' == i));
            res = (res + countDigitSum(s, ind + 1, new_tight, sum + i, minSum, maxSum, dp)) % MOD;
        }
        return dp[ind][tight][sum] = res;
    }
    int count(string num1, string num2, int min_sum, int max_sum) {
        num1 = subtrackOne(num1);
        int n = num2.size();
        vector<vector<vector<long long>>> dp1(n + 1, vector<vector<long long>>(2, vector<long long>(401, -1)));
        vector<vector<vector<long long>>> dp2(n + 1, vector<vector<long long>>(2, vector<long long>(401, -1)));
        long long r = countDigitSum(num2, 0, 1, 0, min_sum, max_sum, dp1);
        long long l = countDigitSum(num1, 0, 1, 0, min_sum, max_sum, dp2);
        return (r - l + MOD) % MOD;
    }
};