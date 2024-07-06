class Solution {
public:
    int numberOfSubarrays1(vector<int>& nums, int k) {
        int sum = 0;
        int n = nums.size();
        int left = 0;
        int right = 0;
        int count = 0;
        for(right=0;right<n;right++){
            sum += nums[right]%2;
            while(left<=right && sum>k){
                sum-=nums[left]%2;
                left++;
            }
            count += right-left+1;
        }
        return count;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        return numberOfSubarrays1(nums,k)- numberOfSubarrays1(nums,k-1);
    }
};