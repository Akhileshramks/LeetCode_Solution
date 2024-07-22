class Solution {
public:
    int ds(int i,int j,string s,string t){
        if(i==0){
            if(j==0 && s[i]==t[j]) return 1;
            else return 0;
        }
        if(j<0) return 1;
        int take = 0;
        int nottake =  ds(i-1,j,s,t);
        if(s[i]==t[j]){
            take = ds(i-1,j-1,s,t);
        }
        return (take+nottake);
    }

    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        int mod = 1e9+7;
        //return ds(n-1,m-1,s,t);
        vector<int> prev(m+1,0);
        prev[0] = 1;
        for(int i=1;i<=n;i++){
            vector<int> curr(m+1,0);
            curr[0] = 1;
            for(int j=1;j<=m;j++){
                int take = 0;
                int nottake = prev[j];
                if(s[i-1]==t[j-1]){
                    take = prev[j-1];
                }
                curr[j] = (take+nottake)%mod;
            }
            prev = curr;
        }
        return prev[m];
    }
};