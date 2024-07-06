class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int prefix_sum = 0;
        int n = nums.size();
        int count = 0;
        unordered_map<int,int> m;
        m[0] = 1;
        for(int i=0;i<n;i++){
            prefix_sum += nums[i];
            count += m[prefix_sum-goal];
            m[prefix_sum]++;
        } 
        return count;
    }
};