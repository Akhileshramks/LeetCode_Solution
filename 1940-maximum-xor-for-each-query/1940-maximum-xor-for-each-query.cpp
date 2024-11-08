class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        int n = nums.size();
        vector<int> ans;
        int x = 0;
        for(int i : nums){
            x ^= i;
            int k = 0;
            int res = 0;
            while(k < maximumBit){
                if(!(1<<k & x)){
                    res |= 1<<k;
                }
                k++;
            }
            ans.push_back(res);
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};