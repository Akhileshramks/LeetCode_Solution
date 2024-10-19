class Solution {
public:
    int subarrays(vector<int>& nums,int k){
        unordered_map<int,int> countMap;
        int low = 0;
        int high = 0;
        int count = 0;
        int n = nums.size();
        while(high < n){
            countMap[nums[high]]++;
            while(countMap.size() > k){
                countMap[nums[low]]--;
                if(countMap[nums[low]] == 0) countMap.erase(nums[low]);
                low++;
            }
            count += (high-low+1);
            high++;
        }
        return count;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return subarrays(nums,k) - subarrays(nums,k-1);
    }
};