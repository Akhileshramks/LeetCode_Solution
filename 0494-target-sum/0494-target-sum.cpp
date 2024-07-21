class Solution {
public:
    int findsumways(int ind,int target,vector<int>& nums){
        if(ind == 0){
            if (target == 0 && nums[0] == 0) return 2;
            else if (target==nums[0] || target==-nums[0]) return 1;
            else return 0;
        } 
        int takenegative = findsumways(ind-1,target+nums[ind],nums);
        int takepositive = findsumways(ind-1,target-nums[ind],nums);
        return takenegative+takepositive;
    }
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        return findsumways(n-1,target,nums);
    }
};