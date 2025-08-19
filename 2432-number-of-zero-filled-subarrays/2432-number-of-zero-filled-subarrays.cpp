class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long count = 0;
        int l = 0,r = 0,n = nums.size();
        while(l < n){
            if(nums[l] == 0){
                if(r < l) r = l;
                while(r < n && nums[r] == 0) r++;
                count += (r - l);
            }
            l++;
        }
        return count;
    }
};