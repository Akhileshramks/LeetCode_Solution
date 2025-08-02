class Solution {
public:
    bool isPossible(vector<int>& piles,int speed,int h){
        int count = 0;
        for(int i = 0;i < piles.size(); i++){
            count += (piles[i] + speed - 1)/speed;
            if(count > h) return false;
        }
        return true;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());
        while(low <= high){
            int mid = low + (high - low)/2;
            if(isPossible(piles,mid,h)){
                high = mid -1;
            }else{
                low = mid + 1;
            }
        }
        return low;
    }

};