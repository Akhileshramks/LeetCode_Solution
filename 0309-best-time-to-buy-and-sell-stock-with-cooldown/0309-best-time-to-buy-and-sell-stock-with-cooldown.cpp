class Solution {
public:
    int maxprof(int ind,int buy,vector<int>& prices){
        if(ind>=prices.size()) return 0;
        int prof;
        if(buy){
            prof = max(-prices[ind]+maxprof(ind+1,0,prices),maxprof(ind+1,1,prices));
        }
        else{
            prof = max(prices[ind]+maxprof(ind+2,1,prices),maxprof(ind+1,0,prices));
        }
        return prof;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        //return maxprof(0,1,prices);
        vector<int> prev(2,0);
        vector<int> curr(2,0);
        vector<int> prevprev(2,0);
        for(int ind=n-1;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                int prof;
                if(buy){
                    prof = max(-prices[ind]+prev[0],prev[1]);
                }
                else{
                    prof = max(prices[ind]+prevprev[1],prev[0]);
                }
                curr[buy] = prof;
            }
            prevprev = prev;
            prev = curr;
        }
        return prev[1];
    }
};