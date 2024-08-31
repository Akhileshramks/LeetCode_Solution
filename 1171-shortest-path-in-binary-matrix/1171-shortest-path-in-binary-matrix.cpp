class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        queue<pair<int,pair<int,int>>> q;
        if(grid[0][0] || grid[n-1][m-1]) return -1;
        vector<vector<bool>> visited(n,vector<bool>(m,false));
        q.push({1,{0,0}});
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            int x = p.second.first;
            int y = p.second.second;
            int d = p.first;
            if(x == n-1 && y == m-1) return d;
            for(int i =-1;i<2;i++){
                for(int j =-1;j<2;j++){
                    int xx = x + i;
                    int yy = y + j;
                    if(xx>=0 && xx<n && yy>=0 && yy<m && grid[xx][yy] == 0 && !visited[xx][yy]){
                        q.push({d+1,{xx,yy}});
                        visited[xx][yy] = true;
                    }
                }
            }
        }
        return -1;
    }
};