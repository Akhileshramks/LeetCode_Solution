class Solution {
public:
    int maxprof(int ind,int buy,int k,vector<int>& prices){
        if(ind == prices.size() || k==0) return 0;
        int prof ;
        if(buy){
            prof = max(-prices[ind]+maxprof(ind+1,0,k,prices),maxprof(ind+1,1,k,prices));
        }
        else{
            prof = max(prices[ind]+maxprof(ind+1,1,k-1,prices),maxprof(ind+1,0,k,prices));
        }
        return prof;
    }
    int maxProfit(vector<int>& prices) {
        //return maxprof(0,1,2,prices);
        int n = prices.size();
        vector<vector<int>> prev(2,vector<int>(3,0));
        vector<vector<int>> curr(2,vector<int>(3,0));
        int prof;
        for(int ind=n-1;ind>=0;ind--){
            for(int buy=0;buy<=1;buy++){
                for(int k=1;k<=2;k++){
                    if(buy){
                        prof = max(-prices[ind]+prev[0][k],prev[1][k]);
                    }
                    else{
                        prof = max(prices[ind]+prev[1][k-1],prev[0][k]);
                    }
                    curr[buy][k] = prof;
                }
            }
            prev = curr;
        }
        return prev[1][2];
    }
};