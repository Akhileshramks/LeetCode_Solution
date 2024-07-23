class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,1);
        vector<int> dp2(n,1);
        for(int ind = 0;ind<n;ind++){
            for(int j=ind+1;j<n;j++){
                if(dp[j]<dp[ind]+1 && nums[j]>nums[ind]){
                    dp[j] = dp[ind]+1;
                }
            }
        }
        for(int ind = n-1;ind>=0;ind--){
            for(int j=ind-1;j>=0;j--){
                if(dp2[j]<dp2[ind]+1 && nums[j]>nums[ind]){
                    dp2[j] = dp2[ind]+1;
                }
            }
        }
        int maxi = 0;
        for(int i=0;i<n;i++){
            if (dp[i] > 1 && dp2[i] > 1) 
            maxi = max(maxi,dp[i]+dp2[i]-1);
        }
        return n-maxi;
    }
};