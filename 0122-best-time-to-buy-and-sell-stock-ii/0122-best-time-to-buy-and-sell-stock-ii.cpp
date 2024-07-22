class Solution {
public:
    int maxprof(int ind,int buy,vector<int>& prices){
        if(ind == prices.size()) return 0;
        int prof;
        if(buy){
            prof = max(-prices[ind]+maxprof(ind+1,0,prices),maxprof(ind+1,1,prices));
        }
        else{
            prof = max(prices[ind]+maxprof(ind+1,1,prices),maxprof(ind+1,0,prices));
        }
        return prof;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> prev(2,0);
        for(int ind=n-1;ind>=0;ind--){
            vector<int> curr(2,0);
            for(int buy=0;buy<=1;buy++){
                int prof;
                if(buy){
                    prof = max(-prices[ind]+prev[0],prev[1]);
                }
                else{
                    prof = max(prices[ind]+prev[1],prev[0]);
                }
                curr[buy] = prof;
            }
            prev = curr;
        }
        return prev[1];
        //return maxprof(0,1,prices);
        // vector<int> prev(n+1,0);
        // int maxi = 0;
        // for(int i =1;i<=n;i++){
        //     vector<int> curr(n+1,0);
        //     for(int j =i+1;j<=n;j++){
        //         curr[j] = max(prev[i-1],prev[i-2]+(prices[j-1]-prices[i-1]));
        //         maxi = max(curr[j],maxi);
        //     }
        //     prev = curr;
        // }
        // return maxi;
    }
};