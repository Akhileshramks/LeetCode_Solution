class Solution {
public:
    int jump(vector<int>& nums) {
        int low = 0,high = 0,farthest = 0;
        int n = nums.size();
        int jump = 0;
        while(high < n - 1){
            for(int i = low; i <= high;i++){
                farthest = max(farthest,i + nums[i]);
            }
            low = high + 1;
            high = farthest;
            jump++;
        }
        return jump;
    }
};