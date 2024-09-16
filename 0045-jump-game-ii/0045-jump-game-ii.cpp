class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int low =0 ,high = 0,jump = 0;
        while(high < n-1){
            int farthest = 0;
            for(int ind = low;ind<=high;ind++){
                farthest = max(farthest,ind+nums[ind]);
            }   
            low = high+1;
            high = farthest;
            jump += 1;
        }
        return jump;
    }
};