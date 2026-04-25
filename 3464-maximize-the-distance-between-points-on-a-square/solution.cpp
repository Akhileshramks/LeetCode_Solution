class Solution {
public:
    bool isPossible(vector<long long>& nums, long long target, int k, int n,int side){
        for(int start = 0;start < n - k + 1;start++){
            int prev  = start;
            int want = k - 1;
            while(want > 0 && prev < n){
                int curr = lower_bound(nums.begin() + prev + 1, nums.end(), nums[prev] + target) - nums.begin();
                if(curr == n) break;
                if((1ll * 4 * side - nums[curr] + nums[start]) >= target){
                    prev = curr;
                    want--;
                }else{
                    break;
                }
            }
            if(want == 0) return true;
        }
        return false;
    }
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        vector<long long> nums;
        for(auto i : points){
            if(i[1] == 0) nums.push_back(i[0]);
            else if(i[0] == side) nums.push_back(side + i[1]);
            else if(i[1] == side) nums.push_back(1ll * 3 * side - i[0]);
            else if(i[0] == 0) nums.push_back(1ll * 4 * side - i[1]);
        }
        int n = nums.size();
        sort(nums.begin(), nums.end());
        long long low = 0, high = 1ll * 4 * side;
        while(low <= high){
            long long mid = low + (high - low) / 2;
            if(isPossible(nums, mid, k, n, side)) low = mid + 1;
            else high = mid - 1; 
        }
        return high;
    }
};