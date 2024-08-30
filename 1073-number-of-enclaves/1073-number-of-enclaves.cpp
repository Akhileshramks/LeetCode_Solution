class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n,vector<bool>(m,false));
        queue<pair<int,int>> q;

        for(int i = 0;i < n;i++){
            if(grid[i][0] == 1) q.push({i,0});
            if(grid[i][m-1] == 1) q.push({i,m-1});
        }
        for(int j=1;j<m-1;j++){
            if(grid[0][j] == 1) q.push({0,j});
            if(grid[n-1][j] == 1) q.push({n-1,j});
        }

        while(!q.empty()){
            auto p = q.front();
            q.pop();
            visited[p.first][p.second] = true;
            vector<pair<int,int>> coordinates = {{0,1},{1,0},{0,-1},{-1,0}};
            for(auto& i : coordinates){
                int xx = i.first + p.first;
                int yy = i.second + p.second;
                
                if(xx>=0 && xx<n && yy>=0 && yy<m && grid[xx][yy] == 1 && !visited[xx][yy]){
                    visited[xx][yy] = true;
                    q.push({xx,yy});
                }

            }
        }
        int ans= 0 ;
        for(int i =0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j] == 1 && visited[i][j] == false){
                    ans++;
                }
            }
        }
        return ans;
    }
};