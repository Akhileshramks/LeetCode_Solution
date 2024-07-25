class Solution {
public:
    int minimumcut(int i,int j,vector<int>& cuts){
        if(i>j) return 0;
        int ans ;
        int mini = INT_MAX;
        for(int cut = i;cut<=j;cut++){
            ans = cuts[j+1]-cuts[i-1] + minimumcut(i,cut-1,cuts) + minimumcut(cut+1,j,cuts);
            mini = min(mini,ans);
        }
        return mini;

    }
    int minCost(int n, vector<int>& cuts) {
        int m = cuts.size();
        cuts.push_back(n);
        cuts.insert(cuts.begin(),0);
        sort(cuts.begin(), cuts.end());
        vector<vector<int>> dp(m+2,vector<int>(m+2,0));
        for(int i=m;i>=1;i--){
            for(int j=1;j<=m;j++){
                if(i>j) continue;
                int ans ;
                int mini = INT_MAX;
                for(int cut = i;cut<=j;cut++){
                    ans = cuts[j+1]-cuts[i-1] + dp[i][cut-1] + dp[cut+1][j];
                    mini = min(mini,ans);
                }
                dp[i][j] = mini;
            }
        }
        return dp[1][m];
        //return minimumcut(1,m,cuts);
    }
};