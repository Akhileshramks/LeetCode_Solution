class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> curr(amount+1,1e8);
        curr[0] = 0;
        for(int ind = 0;ind<n;ind++){
            for(int amt = 1;amt<=amount;amt++){
                if(amt-coins[ind]>=0){
                    curr[amt] = min(curr[amt],1+curr[amt-coins[ind]]);
                }
            }
        }
        return curr[amount]>=(1e8) ? -1: curr[amount];
    }
};