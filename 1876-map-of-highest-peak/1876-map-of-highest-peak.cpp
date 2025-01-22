class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int m = isWater.size();
        int n = isWater[0].size();
        vector<vector<int>> res(m,vector<int>(n,-1));
        queue<pair<int,int>> q;
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n; j++){
                if(isWater[i][j] == 1){
                    q.push({i,j});
                    res[i][j] = 0;
                }
            }
        }
        while(!q.empty()){
            pair<int,int> p = q.front();
            q.pop();
            int x[] = {-1,0,1,0};
            int y[] = {0,1,0,-1};
            for(int i = 0; i < 4;i++){
                int dx = p.first + x[i];
                int dy = p.second + y[i];
                if(dx >= 0 && dx < m && dy >= 0 && dy < n){
                    if(res[dx][dy] == -1){
                        res[dx][dy] = res[p.first][p.second] + 1;
                        q.push({dx,dy});
                    }
                }
            }
        }
        return res;
    }
};