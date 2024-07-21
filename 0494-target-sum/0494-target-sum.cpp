class Solution {
public:
    int findsumways(int ind,int target,vector<int>& nums,unordered_map<string,int>& dp){
        if(ind == 0){
            if (target == 0 && nums[0] == 0) return 2;
            else if (target==nums[0] || target==-nums[0]) return 1;
            else return 0;
        } 
        string key = to_string(ind)+","+to_string(target);
        if(dp.find(key)!=dp.end()) return dp[key];
        int takenegative = findsumways(ind-1,target+nums[ind],nums,dp);
        int takepositive = findsumways(ind-1,target-nums[ind],nums,dp);
        return dp[key] = takenegative+takepositive;
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<string,int> dp;
        int n = nums.size();
        return findsumways(n-1,target,nums,dp);
    }
};