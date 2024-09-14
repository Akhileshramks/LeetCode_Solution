class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxIndex = 0;
        int n= nums.size();
        for(int i=0;i<n;i++){
            if(maxIndex<i) return false;
            maxIndex = max(maxIndex,i+nums[i]);
        }
        return true;
    }
};