class Solution {
public:
    int partitionmaxsum(int i,int n,vector<int>& arr, int k){
        if(i == n) return 0;
        int maxi = 0;
        int maxelement = 0;
        for(int j = i;j<min(n,i+k);j++){
            maxelement = max(maxelement,arr[j]);
            int sum = (j-i+1)*maxelement + partitionmaxsum(j+1,n,arr,k);
            maxi = max(maxi,sum);
        }
        return maxi ;
    }
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n+1,0);
        for(int i=n-1;i>=0;i--){
            int maxi = 0;
            int maxelement = 0;
            for(int j = i;j<min(n,i+k);j++){
                maxelement = max(maxelement,arr[j]);
                int sum = (j-i+1)*maxelement + dp[j+1];
                maxi = max(maxi,sum);
            }
            dp[i] = maxi ;
        }
        return dp[0];
        //return partitionmaxsum(0,n,arr,k);
    }
};