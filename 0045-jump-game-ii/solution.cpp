class Solution {
public:
    int jump(vector<int>& nums) {
        int jumpCount = 1;
        if(nums.size() == 1) return 0;
        int low = 0, high = nums[0];
        int n = nums.size();
        while(high < n - 1){
            int farthest = high;
            for(int i = low;i <= high;i++){
                farthest = max(farthest, nums[i] + i);
            }
            low = high + 1;
            high = farthest;
            jumpCount++;
        }
        return jumpCount;
    }
};