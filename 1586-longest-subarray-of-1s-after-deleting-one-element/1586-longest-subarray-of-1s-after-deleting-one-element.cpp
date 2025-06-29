class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int k = 1;
        int sum = 0, n = nums.size();
        int left = 0, right = 0, ans = 0;
        while(right < n){
            sum += nums[right];
            if((right - left + 1) - sum > k){
                sum -= nums[left];
                left++;
            }
            ans = max(ans, (right-left+1));
            right++;
        }
        return ans - 1;
    }
};