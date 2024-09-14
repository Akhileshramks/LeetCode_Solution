class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int maxi = INT_MIN;
        int count = 0;
        int max_count = 1;
        for(int i =0;i<n;i++){
            if(maxi < nums[i]){
                maxi = nums[i];
                count = 0 ;
                max_count = 0;
            }
            if(nums[i] == maxi) count++;
            else count = 0;
            max_count = max(max_count,count);
        }
        return max_count;
    }
};