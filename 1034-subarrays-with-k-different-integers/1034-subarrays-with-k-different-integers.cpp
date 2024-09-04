class Solution {
public:

    int subarraysWithAtleastKDistinct(vector<int>& nums, int k) {
        unordered_map<int,int> mpp;
        int n = nums.size();
        int l = 0 , r = 0 , noOfSubArray = 0;
        int count = 0;
        while(r<n){
            mpp[nums[r]]++;
            while(mpp.size()>k){
                mpp[nums[l]]--;
                if(mpp[nums[l]] == 0){
                    mpp.erase(nums[l]);
                }
                l++;
            }
            count += r-l+1;
            r++;
        }
        return count;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k){
        return subarraysWithAtleastKDistinct(nums,k) - subarraysWithAtleastKDistinct(nums,k-1);
    }
};