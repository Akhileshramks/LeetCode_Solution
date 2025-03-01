class Solution {
public:
    int lowerBound(int target,vector<int>& nums){
        int n = nums.size();
        int low = 0,high = n-1;
        while(low <= high){
            int mid = low + (high - low)/2;
            if(nums[mid] >= target) high = mid - 1;
            else low = mid + 1;
        }
        return low;
    }
    int upperBound(int target,vector<int>& nums){
        int n = nums.size();
        int low = 0,high = n-1;
        while(low <= high){
            int mid = low + (high - low)/2;
            if(nums[mid] > target) high = mid - 1;
            else low = mid + 1;
        }
        return low;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size() == 0) return {-1,-1};
        int upper = upperBound(target,nums);
        int lower = lowerBound(target,nums);
        if(lower != nums.size() && nums[lower] == target) return {lower,upper-1};
        return {-1,-1};
    }
};