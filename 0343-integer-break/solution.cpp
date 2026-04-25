class Solution {
public:
    int findMaxProduct(vector<int>& nums, int ind, int target,vector<vector<int>> &dp){
        if(target == 0) return 1;
        if(ind  == 0) return target % nums[ind] == 0 ? (int)pow(nums[ind], target / nums[ind]) : 0;
        if(ind < 0) return 0;
        if(dp[ind][target] != -1) return dp[ind][target];
        int notTake = findMaxProduct(nums, ind-1, target, dp);
        int take = 0;
        if(nums[ind] <= target){
            take = findMaxProduct(nums, ind, target-nums[ind], dp);
        }
        take *= nums[ind];
        return dp[ind][target] = max(take, notTake);
    }
    int integerBreak(int n) {
        vector<int> nums;
        vector<vector<int>> dp(n, vector<int>(n+1, -1));
        for(int i = 1;i < n;i++) nums.push_back(i);
        return findMaxProduct(nums, n-2, n, dp);
    }
};