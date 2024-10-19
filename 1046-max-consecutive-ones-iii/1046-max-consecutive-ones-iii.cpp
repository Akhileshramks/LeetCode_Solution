class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0;
        int right = 0;
        int n = nums.size();
        int flip = k;
        int res = INT_MIN;
        while(right < n){
            while(nums[right] == 0 && flip == 0 && left < n){
                if(nums[left] == 0) flip++;
                left++;
            }
            if(nums[right] == 0 && flip > 0) flip--;
            res = max(res,right-left+1);
            right++;
        }
        return res;
    }
};