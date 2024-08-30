class Solution {
public:

    int orangesRotting(vector<vector<int>>& grid) {
        queue<vector<int>> q;
        int n = grid.size();
        int cols = grid[0].size();
        for(int i = 0 ;i<n;i++){
            for(int j = 0;j<cols;j++){
                if(grid[i][j] == 2){
                    q.push({i,j,0});
                }
            }
        }
        int maxi = 0;
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            vector<pair<int,int>> m = {{0,1},{0,-1},{1,0},{-1,0}};
            for(auto x : m){
                int xx = p[0] + x.first;
                int yy = p[1] + x.second;
                if(xx>=0 && xx<n && yy>=0 && yy<cols && grid[xx][yy] == 1){
                    grid[xx][yy] = 2;
                    q.push({xx,yy,p[2]+1});
                    maxi = max(maxi,p[2]+1);
                }
            }
        }
        for(int i = 0 ;i<n;i++){
            for(int j = 0;j<cols;j++){
                if(grid[i][j] == 1) return -1;
            }
        }
        return maxi;
    }
};