class Solution {
public:
    int numSubarrayWithSumAtleastGoal(vector<int>& nums, int goal){
        int l = 0,r = 0,n = nums.size();
        int count = 0;
        int sum = 0;
        for(r = 0;r < n;r++){
            sum += nums[r];
            while(sum > goal && l <= r){
                sum -= nums[l];
                l++;
            }
            count += (r - l + 1);
        }
        return count;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return numSubarrayWithSumAtleastGoal(nums, goal) - numSubarrayWithSumAtleastGoal(nums, goal - 1);
    }
};