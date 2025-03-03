class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> res;
        int n = nums.size();
        for(int i = 0;i < n;i++) if(nums[i] < pivot) res.push_back(nums[i]);
        for(int i = 0;i < n;i++) if(nums[i] == pivot) res.push_back(nums[i]);
        for(int i = 0;i < n;i++) if(nums[i] > pivot) res.push_back(nums[i]);
        return res;
    }
};