class Solution {
public:
    int findMaxJump(vector<int>& nums, int ind, int prev, vector<vector<int>>& dp, int target){
        if(ind < 0) return prev == 0 ? 0 : -1e9;
        if(dp[ind][prev] != -1) return dp[ind][prev];
        int notTake = 0 + findMaxJump(nums, ind - 1, prev, dp, target);
        int take = -1e9;
        if(abs(nums[ind] - nums[prev]) <= target){
            take = 1 + findMaxJump(nums, ind - 1, ind, dp, target);
        }
        return dp[ind][prev] = max(take, notTake);
    }
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n+1, -1));
        int res = findMaxJump(nums, n - 2, n - 1, dp, target);
        return res <  0 ? -1 : res;
    }
};