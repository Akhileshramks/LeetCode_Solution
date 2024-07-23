class Solution {
public:
    int lis(int ind,int prev,vector<int>& nums){
        if(ind==nums.size()) return 0;
        int nottake = 0 + lis(ind+1,prev,nums);
        int take = 0;
        if(prev==-1 || nums[ind]>nums[prev]){
            take = 1 + lis(ind+1,ind,nums);
        }
        return max(take,nottake);
    }
    int lengthOfLIS(vector<int>& nums) {
        //return lis(0,-1,nums);
        int n = nums.size();
        vector<int> dp;
        dp.push_back(nums[0]);
        int len = 1;
        for(int ind = 1;ind<n;ind++){
            if(dp.back()<nums[ind]){
                dp.push_back(nums[ind]);
                len++;
            }
            else{
                int lb = lower_bound(dp.begin(),dp.end(),nums[ind]) - dp.begin();
                dp[lb] = nums[ind];
            }
        }
        return len;
    }
};