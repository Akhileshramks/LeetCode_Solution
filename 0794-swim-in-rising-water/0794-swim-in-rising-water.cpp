class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;
        pq.push({grid[0][0],{0,0}});
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        vector<pair<int,int>> coordinate = {{0,1},{1,0},{-1,0},{0,-1}};
        while(!pq.empty()){
            auto g = pq.top();
            int dist = g.first;
            auto [x,y] = g.second;
            pq.pop();
            if(x == n-1 && y == m-1) return dist;
            for(auto [dx,dy] : coordinate){
                int xx = x+dx;
                int yy = y+dy;
                if(xx>=0 && yy>=0 && xx<n && yy<m && !visited[xx][yy]){
                    pq.push({max(dist, grid[xx][yy]), {xx, yy}});
                    visited[xx][yy] = true;
                }
            }
        }
        return -1;
    }
};