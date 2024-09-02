class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int l= 0;
        int maxi =0;
        int changePossible = k;
        for(int r =0;r<n;r++){
            if( nums[r] == 0){
                changePossible--;
                while(changePossible<0){
                    if(nums[l] == 0) changePossible++;
                    l++;
                }
            }
            maxi = max(maxi,r-l+1);
        }
        return maxi;
    }
};