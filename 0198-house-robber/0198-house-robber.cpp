class Solution {
public:
    int robbery(int ind,vector<int>& nums){
        if(ind == 0) return nums[0];
        int take = nums[ind];
        if(ind>1) take = robbery(ind-2,nums)+nums[ind];
        int nottake = robbery(ind-1,nums);
        return max(take,nottake);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        int prev = nums[0];
        int prev2 = 0;
        int take,nottake;
        for(int ind=1;ind<n;ind++){
            take = nums[ind];
            if(ind>1) take += prev2;
            nottake = prev;
            prev2 = prev;
            prev = max(take,nottake);

        }
        return prev;
    }
};