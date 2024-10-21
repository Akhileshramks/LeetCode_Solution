class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int>> q;
        int n = grid.size();
        int m = grid[0].size();
        for(int i = 0;i < n;i++){
            for(int j =0;j<m;j++){
                if(grid[i][j] == 2) q.push({i,j});
            }
        }
        int count = 0;
        vector<pair<int,int>> coordinates = {{0,-1},{-1,0},{1,0},{0,1}};
        while(!q.empty()){
            int noOfNodes = q.size();
            count++;
            for(int i =0;i < noOfNodes;i++){
                pair<int,int> qFront = q.front();
                int x = qFront.first;
                int y = qFront.second;
                q.pop();
                for(auto c : coordinates){
                    int dx = c.first;
                    int dy = c.second;
                    int xx = x + dx;
                    int yy = y + dy;
                    if(xx >= 0 && xx < n && yy >= 0 && yy < m && grid[xx][yy] == 1){
                        grid[xx][yy] = 2;
                        q.push({xx,yy});
                    }
                }
            }
        }
        for(int i = 0; i < n;i++){
            for(int j = 0;j < m;j++){
                if(grid[i][j] == 1) return -1;
            }
        }
        return count > 0 ? count-1 : 0;
    }
};