class Solution {
public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        bool flag = true;
        vector<vector<int>> res;
        for(int i = 0;i < n;i += 3){
            if(nums[i + 2] - nums[i] > k){
                flag = false;
                break;
            }
            else{
                res.push_back({nums[i],nums[i+1],nums[i+2]});
            }
        }
        if(flag) return res;
        else return {};
    }
};