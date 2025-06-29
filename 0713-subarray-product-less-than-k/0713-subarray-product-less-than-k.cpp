class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int left = 0,right = 0;
        long long prod = 1;
        int n = nums.size();
        int ans = 0;
        for(right = 0;right < n;right++){
            prod *= nums[right];
            while(prod >= k && left <= right){
                prod /= nums[left];
                left++;
            }
            ans += (right - left + 1);
        }
        return ans;
    }
};