class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int low = 0;
        int high = n-1;
        int mid;
        while(low<=high){
            mid = low+(high-low)/2;
            if(nums[mid] == target){
                return true;
            }
            if(nums[mid] == nums[low]  && nums[mid]== nums[high]){
                low+=1;
                high-=1;
                continue;
            }
            else if (nums[low]<=nums[mid]){
                if(nums[low] <= target && target < nums[mid]){
                    high = mid-1;
                }
                else{
                    low = mid+1;
                }
            }
            else if(nums[mid]<=nums[high]){
                if(nums[mid] < target && target <= nums[high]){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }
        }
        return false;
    }
};