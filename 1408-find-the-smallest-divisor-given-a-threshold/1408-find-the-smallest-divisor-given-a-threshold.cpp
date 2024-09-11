class Solution {
public:
    bool isPossible(vector<int>& nums, int divisor, int threshold){
        int current_threshold = 0;
        for(int i : nums){
            current_threshold += (i+divisor-1)/divisor;
        }
        return current_threshold <= threshold;
    }
    int smallestDivisor(vector<int>& nums, int threshold) {
        int low = 1;
        int high = *max_element(nums.begin(), nums.end());
        while(low <= high){
            int mid = low + (high - low)/2;
            if(isPossible(nums,mid,threshold)){
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return low;
    }
};