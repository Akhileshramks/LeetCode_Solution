class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<int> prev(n,0);
        vector<int> curr(n,0);
        for(int m1=0;m1<m;m1++){
            for(int n1 =0 ;n1<n;n1++){
                if(obstacleGrid[m1][n1]){
                    curr[n1] = 0;
                    continue;
                }
                if(m1 == 0 && n1 == 0) {
                    curr[0] = 1;
                    continue;
                }
                int left = m1>0 ? prev[n1] : 0;
                int down = n1>0 ? curr[n1-1] : 0;
                curr[n1] = left+down;
            }
            prev = curr;
        }
        return prev[n-1];
    }
};