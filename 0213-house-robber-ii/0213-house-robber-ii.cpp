class Solution {
public:
    int robbery(vector<int>& nums,int start,int end) {
        int prev = nums[start],prev1 = 0,take,nottake;
        for(int ind=start+1;ind<end;ind++){
            take = nums[ind];
            if(ind>1){
                take+=prev1;
            }
            nottake = prev;
            prev1 = prev;
            prev = max(take,nottake);
        }
        return prev;
    }
    int rob(vector<int>& nums){
        int n = nums.size();
        if(n==1) return nums[0];
        int ans1 = robbery(nums,1,n);
        int ans2 = robbery(nums,0,n-1);
        return max(ans1,ans2);
    }
};