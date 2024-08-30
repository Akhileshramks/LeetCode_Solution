class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        queue<pair<pair<int,int>,int>> q;
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<bool>> visited(n,vector<bool>(m,false));
        vector<vector<int>> result(n,vector<int>(m,0));
        for(int i = 0;i<n;i++)
            for(int j =0;j<m;j++)
                if(mat[i][j] == 0){
                    q.push({{i,j},0});
                    visited[i][j] = true;
                }
                    
        vector<pair<int,int>> coordinates = {{0,1},{0,-1},{1,0},{-1,0}};
        while(!q.empty()){
            auto p = q.front();
            int x = p.first.first;
            int y = p.first.second;
            int d = p.second;
            result[x][y] = d;
            q.pop();
            for(auto & [dx,dy] : coordinates){
                int xx = x + dx;
                int yy = y + dy;
                if(xx>=0 && xx<n && yy>=0 && yy<m && !visited[xx][yy]){
                    q.push({{xx,yy},d+1});
                    visited[xx][yy] = true;
                }
            }
        }
        return result;
    }
};