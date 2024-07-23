class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        vector<int> dp(n,1);
        sort(nums.begin(),nums.end());
        int maxi = 1;
        int last;
        vector<int> parent(n,-1);
        for(int ind = 0;ind<n;ind++){
            for(int j = ind+1;j<n;j++){
                if(nums[j]%nums[ind] == 0 && dp[j]<dp[ind]+1){
                    dp[j] = dp[ind]+1;
                    parent[j] = ind;
                    if(maxi<dp[j]){
                        maxi = dp[j];
                        last = j;
                    }
                }
            }
        }
        while(last!=-1){
            ans.push_back(nums[last]);
            last=parent[last];
        }
        if(ans.size() == 0){
            ans.push_back(nums[0]);
        }
        reverse(ans.begin(),ans.end());
        
        return ans;
    }
};