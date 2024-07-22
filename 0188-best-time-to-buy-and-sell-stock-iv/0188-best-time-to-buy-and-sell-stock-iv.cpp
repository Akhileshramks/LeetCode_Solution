class Solution {
public:
    int maxProfit(int t, vector<int>& prices) {
        int n = prices.size();
        vector<int> prev(t*2+1,0);
        vector<int> curr(t*2+1,0);
        for(int ind=n-1;ind>=0;ind--){
            for(int k=2*t-1;k>=0;k--){
                if(k%2==0){
                    curr[k] = max(-prices[ind]+prev[k+1],prev[k]);
                }
                else{
                    curr[k] = max(prices[ind]+prev[k+1],prev[k]);
                }
            }
            prev = curr;
        }
        return prev[0];
    }
};