class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int left = 0,right = 0;
        int n = nums.size();
        long long sum = 0;
        int ans = 0;
        while(right < n){
            int target = nums[right];
            sum += target;
            if(left <= right && (long long)(right - left + 1) * target - sum > k){
                sum -= nums[left];
                left++;
            }
            ans = max(ans, (right - left + 1));
            right++;
        }
        return ans;
    }

};