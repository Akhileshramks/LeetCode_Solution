class Solution {
public:
    int maxburst(int i,int j,vector<int>& nums,vector<vector<int>> &dp){
        if(i>j) return 0;
        if(dp[i][j]!=-1) return dp[i][j];
        int maxi = 0;
        for(int k=i;k<=j;k++){
            int ans = nums[i-1]*nums[k]*nums[j+1] + maxburst(i,k-1,nums,dp) + maxburst(k+1,j,nums,dp);
            maxi = max(maxi,ans);
        }
        return dp[i][j] = maxi;
    }
    int maxCoins(vector<int>& nums) {
        
        int m = nums.size();
        vector<vector<int>> dp(m+2,vector<int>(m+2,-1));
        nums.push_back(1);
        nums.insert(nums.begin(),1);
        return maxburst(1,m,nums,dp);
    }
};