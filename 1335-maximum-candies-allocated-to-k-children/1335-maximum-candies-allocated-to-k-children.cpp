class Solution {
public:
    bool isPossible(vector<int>& candies,long long k,int target,int n){
        for(int i = n-1;i >= 0 && k > 0;i--){
            int children = candies[i]/target;
            k -= children;
        }
        return k <= 0;
    }
    int maximumCandies(vector<int>& candies, long long k) {
        int n = candies.size();
        sort( candies.begin(),candies.end());
        int low = 1,high = candies[n-1];
        int ans = 0;
        while(low <= high){
            int mid = low + (high - low)/2;
            if(mid != 0 && isPossible(candies,k,mid,n)){
                ans = mid;
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }
        return high;
    }
};