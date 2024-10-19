class Solution {
public:
    int numberOfAtmostSubarrays(vector<int>& nums,int k){
        int sum = 0;
        int count = 0;
        int low = 0;
        int right = 0;
        int n = nums.size();
        while(right < n){
            sum += (nums[right]%2);
            while(sum > k && low <= right){
                sum -= (nums[low]%2);
                low++;
            }
            count += (right - low + 1);
            right++;
        }
        return count;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        return numberOfAtmostSubarrays(nums,k) - numberOfAtmostSubarrays(nums,k-1);
    }
};