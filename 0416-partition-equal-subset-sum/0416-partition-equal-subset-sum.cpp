class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int m = accumulate(nums.begin(), nums.end(), 0);
        if(m%2!=0){
            return false;
        }
        int k = m/2;
        int n = nums.size();
        vector<bool> prev(k+1,false);
        vector<bool> curr(k+1,false);
        bool nottake;
        prev[0] = true;
        if(nums[0]<=k) prev[nums[0]] = true;
        for(int i=1;i<n;i++){
            for(int target=1;target<k+1;target++){
                nottake = prev[target];
                bool take = false;
                if(nums[i]<=target){
                    take = prev[target-nums[i]];
                }
                curr[target] = take|nottake;
            }
            prev = curr;
        }
        return curr[k];
    }
};