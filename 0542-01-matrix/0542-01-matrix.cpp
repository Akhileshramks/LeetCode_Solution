class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        queue<pair<int,int>> q;
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<int>> dist(m,vector<int>(n,-1));
        for(int r = 0;r < m;r++){
            for(int c = 0;c < n;c++){
                if(mat[r][c] == 0){
                    q.push({r,c});
                    dist[r][c] = 0;
                }
            }
        }
        vector<vector<int>> coordinates = {{0,1},{1,0},{0,-1},{-1,0}};
        while(!q.empty()){
            auto [x,y] = q.front();
            q.pop();
            for(int k = 0;k < 4;k++){
                int dx = x + coordinates[k][0];
                int dy = y + coordinates[k][1];
                if(dx >= 0 && dy >= 0 && dx < m && dy < n && dist[dx][dy] == -1){
                    dist[dx][dy] = dist[x][y] + 1;
                    q.push({dx,dy});
                }
            }
        }
        return dist;
    }
};