class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int prev = 0;
        for(int i = 0;i < n;i++) prev += i * nums[i];
        int res = prev;
        for(int i = 1;i < n;i++){
            int new_prev = prev + sum - n * nums[n-i];
            res = max(res, new_prev);
            prev = new_prev;
        }
        return res;
    }
};