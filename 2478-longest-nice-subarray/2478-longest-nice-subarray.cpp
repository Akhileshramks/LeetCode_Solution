class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size();
        int maxi = 0;
        for(int i = 0;i < n;i++){
            int orRes = 0; 
            int j = i;
            while(j < n && ((orRes & nums[j]) == 0)){
                orRes = (orRes|nums[j]);
                j++;
            }
            maxi = max(maxi,j - i);
        }
        return maxi;
    }
};
/*
3 -  000011
8 -  000100
48 - 011000

*/