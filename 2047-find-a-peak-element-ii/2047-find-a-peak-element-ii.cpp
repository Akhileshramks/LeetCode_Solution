class Solution {
public:
    int findMaximum(vector<int>& row){
        int n = row.size();
        int ind = -1;
        int maxi = INT_MIN;
        for(int i=0;i<n;i++){
            if(maxi<row[i]){
                maxi = row[i];
                ind = i;
            }
        }
        return ind;
    }
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int low = 0;
        int high = n-1;
        while(low <= high){
            int mid = low + (high-low)/2;
            int ind = findMaximum(mat[mid]);
            int val = mat[mid][ind];
            int top = mid-1 >=0 ? mat[mid-1][ind] : -1;
            int bottom = mid+1 <n ? mat[mid+1][ind] : -1;
            if(val > top && val > bottom) return {mid,ind};
            else if(top>val) high = mid-1;
            else low = mid+1;
        }
        return {-1,-1};
    }
};