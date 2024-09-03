class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int l = 0,r = n-1,lsum = 0,rsum = 0;
        for(int i=0;i<k;i++) lsum+=cardPoints[i];
        int maxi = lsum;
        for(l = k-1;l>=0;l--){
            rsum += cardPoints[r];
            lsum -= cardPoints[l];
            maxi = max(maxi,lsum+rsum);
            r--;
        }
        return maxi;
    }
};