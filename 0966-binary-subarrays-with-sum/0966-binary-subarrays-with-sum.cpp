class Solution {
public:
    // int numSubarrayWithSumAtleastGoal(vector<int>& nums, int goal){
    //     int l = 0,r = 0,n = nums.size();
    //     int count = 0;
    //     int sum = 0;
    //     for(r = 0;r < n;r++){
    //         sum += nums[r];
    //         while(sum > goal && l <= r){
    //             sum -= nums[l];
    //             l++;
    //         }
    //         count += (r - l + 1);
    //     }
    //     return count;
    // }
    // int numSubarraysWithSum(vector<int>& nums, int goal) {
    //     return numSubarrayWithSumAtleastGoal(nums, goal) - numSubarrayWithSumAtleastGoal(nums, goal - 1);
    // }
    int numSubarraysWithSum(vector<int>& nums, int goal){
        int n = nums.size();
        int currSum = 0;
        int zeroCount = 0;
        int l = 0;
        int res = 0;
        for(int r = 0;r < n;r++){
            currSum += nums[r];
            while(l < r && (nums[l] == 0 || currSum > goal)){
                if(nums[l] == 0) zeroCount++;
                else zeroCount = 0;

                currSum -= nums[l];
                l++;
            }
            if(currSum == goal) res += 1 + zeroCount;
        }
        return res;
    }

};