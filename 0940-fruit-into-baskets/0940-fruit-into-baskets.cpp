class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int k = 2;
        unordered_map<int,int> lastSeen;
        int ans = 0;
        int left = 0,right = 0,n = fruits.size();
        for(right = 0;right < n;right++){
            lastSeen[fruits[right]] = right;
            if(lastSeen.size() > k && left <= right){
                int minIdx = INT_MAX;
                int fruitToRemove = -1;
                for(auto [fruit,idx] : lastSeen){
                    if(idx < minIdx){
                        minIdx = idx;
                        fruitToRemove = fruit;
                    }
                }
                left = minIdx + 1;
                lastSeen.erase(fruitToRemove);
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};