class Solution {
public:
    int coinchange(int ind,int amount,vector<int>& coins){
        if(ind==0){
            return amount%coins[0]==0;
        }
        //if(amount==0) return 1;
        int nottake = coinchange(ind-1,amount,coins);
        int take = 0;
        if(coins[ind]<=amount){
            take = coinchange(ind,amount-coins[ind],coins);
        }
        return take+nottake;
    }
    int change(int amt, vector<int>& coins) {
        int n = coins.size();
        //return coinchange(n-1,amount,coins);
        vector<int> prev(amt+1,0);
        for(int i =0;i<=amt;i++)
            prev[i] = i%coins[0]==0 ;
        for(int ind=1;ind<n;ind++){
            vector<int> curr(amt+1,0);
            for(int amount = 0;amount<=amt;amount++){
                int nottake = prev[amount];
                int take = 0;
                if(coins[ind]<=amount){
                    take = curr[amount-coins[ind]];
                }
                curr[amount] = take+nottake;
            }
            prev = curr;
        }
        return prev[amt];
    }
};