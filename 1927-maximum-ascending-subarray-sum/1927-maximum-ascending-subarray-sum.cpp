class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int maxi = nums[0];
        int n = nums.size();
        int sum = nums[0];
        for(int i = 1;i < n;i++){
            if(nums[i-1] < nums[i]){
                sum += nums[i];
            }
            else{
                sum = nums[i];
            }
            maxi = max(maxi,sum);
        }
        return maxi;
    }
};