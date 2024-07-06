class Solution {
public:
    int numSubarraysWithSum1(vector<int>& nums, int goal) {
        int prefix_sum = 0;
        int n = nums.size();
        int count = 0;
        int left=0,right =0;
        for(right=0;right<n;right++){
            prefix_sum += nums[right];
            while(left<=right && prefix_sum>goal){
                prefix_sum -= nums[left];
                left++;
            }
            count += right-left+1;
        }
        return count;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
    return numSubarraysWithSum1(nums,goal) -numSubarraysWithSum1(nums,goal-1);
    }
};