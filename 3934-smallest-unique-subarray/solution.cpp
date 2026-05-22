class Solution {
public:
    bool isPossible(vector<int>& nums, int len){
        long long prime = 1e5 + 3;
        long long MOD = (1LL << 31) - 1;
        long long power = 1, hash = 0;
        int n = nums.size();
        unordered_map<long long,int> mpp;
        for(int i = 0;i < len;i++){
            power = (power * prime) % MOD;
            hash = ((prime * hash) + nums[i]) % MOD;
        }
        mpp[hash]++;
        for(int i = len; i < n;i++){
            hash = ((hash * prime) + nums[i] - nums[i - len] * power) % MOD;
            hash = (hash + MOD) % MOD;
            mpp[hash]++;
        }
        for(auto [key, val] : mpp) if(val == 1) return true;
        return false;
    }
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        int low = 1, high = n;
        while(low <= high){
            int mid = low + (high - low) / 2;
            if(isPossible(nums, mid)) high = mid - 1;
            else low = mid + 1;
        }
        return low;
    }
};