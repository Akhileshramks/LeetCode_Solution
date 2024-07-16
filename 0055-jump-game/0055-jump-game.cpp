class Solution {
public:
    bool canJump(vector<int>& nums) {
        int steps = nums[0];
        int n = nums.size();
        if(n==1) return true;
        if(steps == 0) return false;
        if(steps>=n-1) return true;
        int maxreach = steps;
        bool reach = false;
        for(int i = 1;i<n;i++){
            if(steps){
                maxreach = max(i+nums[i],maxreach);
            }
            if(i==n-1 && steps>0) reach = true;
            steps--;

            if(steps == 0){
                steps = maxreach-i;
            }
        }
        return reach;
    }
};