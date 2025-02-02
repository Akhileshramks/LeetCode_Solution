class Solution {
public:
    bool check(vector<int>& nums) {
        int inversionCount = 0;
        int n = nums.size();
        if(nums[0] < nums[n-1]) inversionCount++;
        for(int i = 1;i < n;i++){
            if(nums[i-1] > nums[i]) inversionCount++;
        }
        return inversionCount <= 1;
    }
};