class Solution {
public:
    bool isPossible(vector<int>& weights,int weight,int days){
        int ans = 1;
        int weight_sum = 0;
        for(int i : weights){
            weight_sum += i;
            if(weight_sum > weight){
                ans++;
                weight_sum = i;
            }
        }
        return ans <= days;
    }
    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();
        int low = *max_element(weights.begin(),weights.end());
        int high = accumulate(weights.begin(),weights.end(),0);
        while(low <= high){
            int mid = low + (high-low)/2;
            if(isPossible(weights,mid,days)){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return low;
    }
};