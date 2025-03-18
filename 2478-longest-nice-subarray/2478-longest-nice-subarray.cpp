class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size();
        int low = 0, high = 0;
        int orRes = 0;
        int maxi = 0;
        while(high < n){
            while(low < high && ((orRes & nums[high]) != 0)){
                orRes ^= nums[low];
                low++;
            }
            orRes |= nums[high];
            high++;
            maxi = max(maxi, high - low);
        }
        return maxi;
    }
};