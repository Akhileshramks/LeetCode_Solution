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
        vector<int> prevDp(n, INT_MIN);
        int res = -1;
        prevDp[0] = 0;
        for(int ind = 0;ind <= n - 2;ind++){
            vector<int> currDp(n, INT_MIN);
            for(int prev = 0;prev <= n - 1;prev++){
                int notTake = 0 + prevDp[prev];
                int take = -1e9;
                if(abs(nums[ind] - nums[prev]) <= target){
                    take = 1 + prevDp[ind];
                }
                currDp[prev] = max(take, notTake);
            }
            prevDp = currDp;
        }
        return max(res, prevDp[n-1]);
    }
};