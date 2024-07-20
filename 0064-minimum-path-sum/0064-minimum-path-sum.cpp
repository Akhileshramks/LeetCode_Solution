class Solution {
public:
    int minpathsum(int n,int m,vector<vector<int>>& grid){
        if(m == 0 && n == 0) return grid[0][0];
        int left = (m>0) ? minpathsum(n,m-1,grid) : INT_MAX;
        int up = (n>0) ? minpathsum(n-1,m,grid) : INT_MAX;
        int mini = min(left,up);
        return mini == INT_MAX ? INT_MAX: mini+grid[n][m];
    }
    int minPathSum(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        //return minpathsum(n-1,m-1,grid);
        vector<int> prev(cols,INT_MAX),curr(cols,INT_MAX);
        for(int n=0;n<rows;n++){
            for(int m=0;m<cols;m++){
                if(m==0 && n==0){
                    curr[0] = grid[0][0];
                    continue;
                }
                int left = (m>0) ? curr[m-1] : INT_MAX;
                int up = (n>0) ? prev[m] : INT_MAX;
                int mini = min(left,up);
                curr[m] = (mini == INT_MAX) ? INT_MAX: mini+grid[n][m]; 
            }
            prev = curr;
        }
        return prev[cols-1];
    }
};