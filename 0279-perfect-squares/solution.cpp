class Solution {
public:
    int countMinElements(vector<int>& nums, int ind, int target,vector<vector<int>>& dp){
        if(target == 0) return 0;
        if(ind == 0){
            return target % nums[ind] == 0 ?  target / nums[ind] : INT_MAX;
        }
        if(dp[ind][target] != -1) return dp[ind][target];
        int notTake = countMinElements(nums, ind - 1, target, dp);
        int take = INT_MAX;
        if(nums[ind] <= target){
            take = min(take, countMinElements(nums,ind,target - nums[ind], dp));
        }
        if(take != INT_MAX) take += 1;
        return dp[ind][target] = min(take, notTake);
    }
    int numSquares(int n) {
        vector<int> nums;
        int currSum = 3;
        int perfectSquare = 1;
        for(int i = 1; perfectSquare <= n;currSum += 2){
            nums.push_back(perfectSquare);
            perfectSquare += currSum;
        }
        int m = nums.size();
        vector<vector<int>> dp(m, vector<int>(n+1, -1));
        return countMinElements(nums, m-1, n, dp);

    }
};