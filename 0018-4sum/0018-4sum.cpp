class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        if(n<4) return res;
        for(int i = 0;i<n;i++){
            if(i>0 && nums[i] == nums[i-1]) continue;
            for(int j = i+1;j<n;j++){
                if(j>i+1 && nums[j] == nums[j-1]) continue;
                int k = j+1;
                int l = n-1;
                long target2 =(long)target - nums[i] - nums[j];
                while(k<l){
                    long sum = nums[k] + nums[l];
                    if(target2 == sum){
                        res.push_back({nums[i],nums[j],nums[k],nums[l]});
                        while(k<l && nums[k]==nums[k+1]) k++;
                        while(k<l && nums[l] == nums[l-1]) l--;
                        k++;
                        l--;
                    }
                    else if(sum>target2) l--;
                    else k++;
                }
            }
        }
        return res;
    }
};