class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int prefixProduct = 1;
        int maxi = INT_MIN;
        int suffixProduct = 1;
        int n = nums.size();
        for(int i =0;i<n;i++){
            prefixProduct *= nums[i];
            suffixProduct *= nums[n-i-1];
            maxi = max(maxi,max(suffixProduct,prefixProduct));
            if(prefixProduct == 0) prefixProduct = 1;
            if(suffixProduct == 0) suffixProduct = 1;
        }
        return maxi;
    }
};