class Solution {
public:
    vector<vector<int>> directions = {{-1,-1}, {-1,1}, {1,1}, {1,-1}};
    bool isValid(int n,int m, int x,int y){
        if(x >= 0 && y >= 0 && x <= n - 1 && y <= m - 1) return true;
        return false;
    }
    int maxLength(vector<vector<int>>& grid,int x,int y,int turn,int direction,int prev,int n,int m,vector<vector<vector<vector<int>>>>& memo){
        if(memo[x][y][direction][turn] != -1) return memo[x][y][direction][turn];
        int dx = x + directions[direction][0];
        int dy = y + directions[direction][1];
        int noTurn = 0;
        int turnRes = 0;
        int need;
        if(prev == 2) need = 0;
        else need = 2;
        if(isValid(n, m,dx, dy) && grid[dx][dy] == need){
            noTurn = maxLength(grid, dx, dy, turn, direction, need, n, m, memo);
        }
        if(turn == 0){
            int tdx = x + directions[(direction+1)%4][0];
            int tdy = y + directions[(direction+1)%4][1];
            if(isValid(n, m, tdx, tdy) && grid[tdx][tdy] == need){
                turnRes = maxLength(grid, tdx, tdy, 1, (direction + 1)%4, need, n, m, memo);
            }
        }
        return memo[x][y][direction][turn] = 1 + max(noTurn,turnRes);
    }
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        bool atleast1 = false;
        int res = 0;
        vector<vector<vector<vector<int>>>> memo(n, vector<vector<vector<int>>>(m, vector<vector<int>>(4, vector<int>(2, -1))));        
        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                if(grid[i][j] == 1){
                    atleast1 = true;
                    for(int k = 0;k < 4;k++){
                        int dx = i + directions[k][0];
                        int dy = j + directions[k][1];
                        if(isValid(n, m, dx, dy) && grid[dx][dy] == 2){
                            res = max(res, maxLength(grid, dx, dy, 0, k, 2, n, m, memo));
                        }
                    }
                }
            }
        }
        return res == 0 ? atleast1 ? 1 : 0 : res + 1;
    }
};