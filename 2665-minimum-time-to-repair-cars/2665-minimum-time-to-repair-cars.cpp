class Solution {
public:
    bool isPossible(vector<int>& ranks,int cars,long long target){
        int n = ranks.size();
        for(int i = 0;i < n && cars > 0;i++){
            cars -= static_cast<int>(sqrt(target/ranks[i]));
        }
        return cars <= 0;
    }
    long long repairCars(vector<int>& ranks, int cars) {
        long long low = 1;
        long long high = 1ll * *min_element(ranks.begin(),ranks.end()) * cars * cars;
        while(low <= high){
            long long mid = low + (high - low)/2;
            if(isPossible(ranks,cars,mid)){
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        return low;
    }
};