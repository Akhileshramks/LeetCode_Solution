class Solution {
public:
    bool isPossible(int mountainHeight, vector<int>& workerTimes, long long time){
        int len_w = workerTimes.size();
        for(int i = 0 ; i < len_w; i++ ){
            if(mountainHeight > 0){
                long long c = time * 2 / workerTimes[i];
                int n = (-1 + sqrt(1 + 4 * c)) / 2;
                mountainHeight -= n;
            }
        }
        return mountainHeight <= 0;
    }

    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long low = 0;
        int maxi = *max_element(workerTimes.begin(), workerTimes.end());
        long long high = 1LL * mountainHeight * (mountainHeight + 1) * maxi / 2;
        long long ans;
        while(low <= high){
            long long mid = low + (high - low) / 2;
            if(isPossible(mountainHeight, workerTimes, mid)){
                high = mid - 1;
                ans = mid;
            } 
            else low = mid + 1;
        }
        return ans;
    }
};