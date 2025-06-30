class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int l = 0, n = nums.size(), r = 0;
        int ans = 0;
        for(r = 0;r < n;r++){
            while(l <= r && nums[r] - nums[l] > 1) l++;
            if(nums[r] - nums[l] == 1) ans = max(ans, r - l + 1);
        }
        return ans;
    }
};