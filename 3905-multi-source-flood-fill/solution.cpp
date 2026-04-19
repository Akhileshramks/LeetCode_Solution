class Solution {
public:
    static bool comp(vector<int> &a, vector<int> &b){
        return a[2] > b[2]; 
    }
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
        queue<pair<pair<int,int>,int>> q;
        vector<vector<int>> grid(n, vector<int>(m, 0));
        sort(sources.begin(),sources.end(),comp);
        for(auto&i : sources){
            q.push({{i[0],i[1]}, i[2]});
            if(grid[i[0]][i[1]] == 0) grid[i[0]][i[1]] = i[2];
        }
        while(!q.empty()){
            auto top = q.front();
            q.pop();
            int dx[] = {-1,1,0,0};
            int dy[] = {0,0,1,-1};
            for(int i = 0;i < 4;i++){
                int x = top.first.first;
                int y = top.first.second;
                int color = top.second;
                int dxx = x + dx[i];
                int dyy = y + dy[i];
                if(dxx >= 0 && dyy >= 0 && dxx < n && dyy < m){
                    if(grid[dxx][dyy] == 0){
                        grid[dxx][dyy] = color;
                        q.push({{dxx, dyy}, color});
                    }
                }
            }
        }
        return grid;
    }
};