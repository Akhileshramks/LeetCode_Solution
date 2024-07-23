class Solution {
public:
    bool predecessor(string& w1,string& w2){
        int n = w1.size();
        int m =w2.size();
        if(n != m-1) return false;
        int i = 0,j=0,k=0;
        while(i<n && k<=1){
            if(w1[i] == w2[j]){
                i++;
                j++;
            }
            else{
                j++;
                k++;
            }
        }
        return i==n;
    }
    int longestStrChain(vector<string>& words) {
        int n = words.size();
        vector<int> dp(n,1);
        sort(words.begin(),words.end(),[](const string& w1,const string& w2){return w1.size()<w2.size();});
        int maxi = 1;
        for(int ind=0;ind<n;ind++){
            for(int j=ind+1;j<n;j++){
                if(predecessor(words[ind],words[j]) && dp[j]<dp[ind]+1){
                    dp[j] = dp[ind]+1;
                    maxi = max(maxi,dp[j]);
                }
            }
        }
        return maxi;
    }
};