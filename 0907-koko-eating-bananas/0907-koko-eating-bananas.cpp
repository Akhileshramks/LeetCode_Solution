class Solution {
public:
    long eatspeed(vector<int>& piles,int m){
        long count = 0;
        for(auto i : piles){
            count+=(i+m-1)/m;
        }
        return count;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        long maxi = *max_element(piles.begin(),piles.end());
        int n = piles.size();
        long low = 1;
        long high = maxi;
        long mid;
        while(low<=high){
            mid = low + (high-low)/2;
            if(eatspeed(piles,mid)<=h){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return low;
    }
};