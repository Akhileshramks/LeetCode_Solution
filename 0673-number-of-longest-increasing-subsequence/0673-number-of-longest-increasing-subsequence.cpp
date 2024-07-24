class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,1);
        int maxi = 1;
        vector<int> count(n,1);
        int lastind = 0;
        for(int ind=0;ind<n;ind++){
            for(int j=0;j<ind;j++){
                if(dp[ind]<dp[j]+1 && nums[j]<nums[ind]){
                    dp[ind] = dp[j]+1;
                    count[ind] = count[j];
                }
                else if(nums[ind]>nums[j] && dp[ind] == dp[j]+1){
                    count[ind]+=count[j];
                }
            }
            maxi = max(maxi,dp[ind]);
        }
        int sum = 0;
        for(int i =0;i<n;i++){
            if(dp[i] == maxi){
                sum+=count[i];
            }
        }
        return sum;
    }
};