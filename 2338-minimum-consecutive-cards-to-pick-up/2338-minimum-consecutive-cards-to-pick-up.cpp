class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        int ans = INT_MAX;
        unordered_map<int,int> mpp;
        for(int i = 0 ;i < cards.size();i++){
            if(mpp.find(cards[i]) != mpp.end()){
                ans = min(ans,i-mpp[cards[i]]+1);
            }
            mpp[cards[i]] = i;
        }
        return ans == INT_MAX ? -1 : ans;
    }
};