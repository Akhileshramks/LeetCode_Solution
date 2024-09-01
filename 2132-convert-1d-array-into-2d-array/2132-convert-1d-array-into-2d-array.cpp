class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        int n1 = original.size();
        if(m*n != n1) return {};
        int a = 0;
        vector<vector<int>> res(m,vector<int>(n));
        for(int i=0;i<m;i++){
            for(int j =0;j<n;j++){
                res[i][j] = original[a];
                a++;
            }
        }
        return res;
    }
};