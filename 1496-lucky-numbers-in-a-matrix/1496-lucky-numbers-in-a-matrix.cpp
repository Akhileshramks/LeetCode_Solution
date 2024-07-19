class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> arr1(n, INT_MAX);
        vector<int> arr2(m, INT_MIN);
        for(int i = 0;i<n;i++){
            for(int j =0;j<m;j++){
                arr1[i] = min(arr1[i],matrix[i][j]);
                arr2[j] = max(arr2[j],matrix[i][j]);
            }
        }
        vector<int> res;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(arr1[i] == arr2[j]){
                    res.push_back(arr1[i]);
                }
            }
        }
        return res;
    }
};