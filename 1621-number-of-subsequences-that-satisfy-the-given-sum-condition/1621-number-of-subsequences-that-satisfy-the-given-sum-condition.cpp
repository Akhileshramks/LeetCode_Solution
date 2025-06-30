
class Solution {
public:
    int MOD = 1e9 + 7;
    int powerOf2(int exponent){
        long base = 2,prod = 1;
        while(exponent > 0){
            if(exponent % 2 == 1){
                prod = (prod * base) % MOD;
                exponent--;
            }
            else{
                base = (base * base) % MOD;
                exponent /= 2;
            }
        }
        return prod;
    }
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int l = 0, n = nums.size(), r = n - 1;
        int count = 0;
        while(l <= r){
            while(l <= r && nums[l] + nums[r] > target){
                r--;
            }
            if(l <= r && nums[l] + nums[r] <= target){
                count = (count + powerOf2(r - l)) % MOD;
            }
            l++;
        }
        return count;
    }
};