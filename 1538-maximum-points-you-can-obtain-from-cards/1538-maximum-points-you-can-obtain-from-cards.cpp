class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int window = n - k;
        int l =0;
        int r = 0;
        int sum =0;
        int total = 0;
        int mini = INT_MAX;
        while(r<n){
            while(l<=r && r-l >= window){
                sum -= cardPoints[l];
                l++;
            }
            
            total += cardPoints[r];
            sum += cardPoints[r];
            if(r-l+1 == window) mini = min(mini,sum);
            r++;
        }
        return total - mini;

    }
};