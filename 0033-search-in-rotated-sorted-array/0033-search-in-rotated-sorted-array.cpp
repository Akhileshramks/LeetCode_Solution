class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int low = 0, high = n-1;
        while(low <= high){
            int mid = low + (high - low)/2;
            if(nums[mid] == target) return mid;
            else if((nums[low] <= nums[mid] && nums[low] <= target && target <= nums[mid]) || (nums[mid] <= nums[high] && (target < nums[mid] || target > nums[high]))){
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return -1;
    }
};