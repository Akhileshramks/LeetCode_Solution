class Solution {
public:
    void solve(vector<vector<char>>& board) {
        queue<pair<int,int>> q;
        int n = board.size();
        int m = board[0].size();

        vector<vector<bool>> visited(n,vector<bool>(m,false));
        vector<pair<int,int>> coordinates = {{0,1},{1,0},{-1,0},{0,-1}};

        for(int i = 0;i < n;i ++ ){
            for(int j = 0;j < m;j ++){
                if( i == 0 || i == n-1 || j == 0 || j == m-1){
                    if(board[i][j] == 'O'){
                        q.push({i,j});
                        visited[i][j] = true;
                    }
                }
            }
        }

        while(!q.empty()){
            auto p = q.front();
            int x = p.first;
            int y = p.second;
            q.pop();
            for(auto &[dx,dy] : coordinates){
                int xx = x + dx;
                int yy = y + dy;

                if(xx >=0 && xx < n && yy >= 0 && yy < m && board[xx][yy] == 'O' && !visited[xx][yy]){
                    visited[xx][yy] = true;
                    q.push({xx,yy});
                }
            }
        }

        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(!visited[i][j] && board[i][j] == 'O'){
                    board[i][j] = 'X';
                }
            }
        }
    }
};