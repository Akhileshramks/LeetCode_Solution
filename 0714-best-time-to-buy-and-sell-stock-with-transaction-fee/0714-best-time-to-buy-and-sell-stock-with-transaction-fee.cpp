class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<int> prev(2,0);
        vector<int> curr(2,0);
        for(int ind=n-1;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                int prof;
                if(buy){
                    prof = max(-prices[ind]+prev[0],prev[1]);
                }
                else{
                    prof = max(prices[ind]+prev[1]-fee,prev[0]);
                }
                curr[buy] = prof;
            }
            prev = curr;
        }
        return prev[1];
    }
};