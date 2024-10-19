class Solution {
public:
    int numSunarraysWithAtmostSum(vector<int>&nums,int goal){
        int sum = 0;
        int n = nums.size();
        int count = 0;
        int l = 0;
        for(int i = 0;i < n;i++){
            sum += nums[i];
            while(l <= i && sum > goal){
                sum -= nums[l];
                l++;
            }
            count += (i-l+1);
        }
        return count;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return (numSunarraysWithAtmostSum(nums,goal) - numSunarraysWithAtmostSum(nums,goal-1));
    }
};