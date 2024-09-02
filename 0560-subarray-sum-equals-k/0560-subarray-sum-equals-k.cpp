class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> pre;
        int n = nums.size();
        int prefixsum =0;
        pre[0] = 1;
        int count =0;
        for(int i =0;i<n;i++){
            prefixsum += nums[i];
            count+=pre[prefixsum-k];
            pre[prefixsum]++;
        }
        return count;
    }
};