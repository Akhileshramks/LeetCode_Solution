class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int m = accumulate(nums.begin(), nums.end(), 0);

        if(m%2!=0){
            return false;
        }
        int k = m/2;
        int n = nums.size();
        vector<vector<bool>> dp(n,vector<bool>(k+1,false));
        
        bool nottake;
        for(int i=0;i<n;i++){
            dp[i][0] = true;
        }
        if(nums[0]<=k) dp[0][nums[0]] = true;
        for(int i=1;i<n;i++){
            for(int target=1;target<k+1;target++){
                nottake = dp[i-1][target];
                bool take = false;
                if(nums[i]<=target){
                    take = dp[i-1][target-nums[i]];
                }
                dp[i][target] = take|nottake;
            }
           
        }
        return dp[n-1][k];
    }
};