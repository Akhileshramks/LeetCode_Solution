class Solution {
public:
    bool isPossible(vector<int>& nums,int target,int k){
        int ans = 1;
        int sum = 0;
        for(int i : nums){
            sum += i;
            if(sum > target){
                ans++;
                sum = i;
                if (ans > k) {
                    return false;
                }
            }
        }
        return true ;
    }
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        int low = *max_element(nums.begin(),nums.end());
        int high = accumulate(nums.begin(),nums.end(),0);
        while(low <= high){
            int mid = low + (high-low)/2;
            if(isPossible(nums,mid,k)){
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return low;
    }
};