class Solution {
public:
    int numSubarraysWithSum1(vector<int>& nums, int goal) {
        int n = nums.size();
        int sum = 0;
        int l =0;
        int count = 0;
        for(int r=0;r<n;r++){
            sum+=nums[r];
            while(l<=r && sum>goal){
                sum-=nums[l];
                l++;
            }
            count += r-l+1;
        }
        return count;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal){
        return numSubarraysWithSum1(nums,goal) - numSubarraysWithSum1(nums,goal-1);
    }
};