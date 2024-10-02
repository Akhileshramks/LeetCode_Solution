class Solution {
public:
    int minConLen(vector<string>& words,int ind,char start,char end,vector<vector<vector<int>>>& dp){
        if(ind >= words.size()) return 0;
        if(dp[ind][start-'a'][end-'a'] != -1) return dp[ind][start-'a'][end-'a'];
        int len = words[ind].size();
        int firstMatch = len + minConLen(words,ind+1,start,words[ind][len-1],dp);
        int lastMatch = len + minConLen(words,ind+1,words[ind][0],end,dp);
        if(words[ind][0] == end) firstMatch -= 1;
        if(words[ind][len-1] == start) lastMatch -= 1;
        return dp[ind][start-'a'][end-'a'] = min(firstMatch,lastMatch);
    }
    int minimizeConcatenatedLength(vector<string>& words) {
        int n = words.size();
        int m = words[0].size();
        vector<vector<vector<int>>> dp(n,vector<vector<int>> (26,vector<int> (26,-1)));
        return m + minConLen(words,1,words[0][0],words[0][m-1],dp);
    }
};