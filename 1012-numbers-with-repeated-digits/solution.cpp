class Solution {
public:
    int countDigitAtleastOneRepeated(string s, int ind, int tight, int bitMap, int isRepeat, int started, vector<vector<vector<vector<int>>>> &dp){
        if(ind == s.size()) return isRepeat;
        if(dp[ind][tight][bitMap][isRepeat] != -1) return dp[ind][tight][bitMap][isRepeat];
        int limit = tight ? s[ind] - '0' : 9;
        int res = 0;
        for(int i = 0;i <= limit;i++){
            int new_tight = (tight & (i == s[ind] - '0'));
            int new_isRepeat = isRepeat;
            int new_started = started || (i != 0);
            if(!new_started){
                res += countDigitAtleastOneRepeated(s, ind + 1, new_tight, bitMap, isRepeat, new_started, dp);
                continue;
            }
            if(1 << i & bitMap) new_isRepeat = 1;
            int new_bitMap = bitMap | (1 << i);
            res += countDigitAtleastOneRepeated(s, ind + 1, new_tight, new_bitMap, new_isRepeat, new_started, dp);
        }
        return dp[ind][tight][bitMap][isRepeat] = res;
    }
    int numDupDigitsAtMostN(int n) {
        string s = to_string(n);
        vector<vector<vector<vector<int>>>> dp(s.size() + 1, vector<vector<vector<int>>>(2, vector<vector<int>>(1 << 10, vector<int>(2, -1))));
        return countDigitAtleastOneRepeated(s, 0, 1, 0, 0, 0, dp);
    }
};