class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int time = 0;
        int m = grid.size();
        int n = grid[0].size();
        int freshCount = 0;
        queue<pair<int,int>> q;
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                if(grid[i][j] == 2) q.push({i,j});
                else if(grid[i][j] == 1) freshCount++;
            }
        }
        int dx[4] = {0,0,-1,1};
        int dy[4] = {-1,1,0,0};
        while(!q.empty()){
            int len = q.size();
            for(int i = 0;i < len;i++){
                auto top = q.front();
                q.pop();
                int x = top.first;
                int y = top.second;
                for(int k = 0;k < 4;k++){
                    int dxx = x + dx[k];
                    int dyy = y + dy[k];
                    if(dxx >= 0 && dyy >= 0 && dxx < m && dyy < n && grid[dxx][dyy] == 1){
                        freshCount--;
                        q.push({dxx,dyy});
                        grid[dxx][dyy] = 2;
                    }
                }
            }
            if(!q.empty()) time++;
        }

        return freshCount == 0 ? time : -1;
    }
};