class Solution {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int cutoff = *max_element(queries.begin(),queries.end());
        int ind;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        int n = grid.size();
        int m = grid[0].size();
        int k = queries.size();
        for(int i = 0;i < k;i++){
            pq.push({queries[i],i});
            if(queries[i] == cutoff) ind = i;
        }
        vector<int> result(k,0);
        priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> gridEntry;
        int res = 0;
        vector<vector<bool>> visited(n,vector<bool>(m,false));
        if(grid[0][0] < cutoff){
            gridEntry.push({grid[0][0],{0,0}});
            visited[0][0] = true;
        }
        
        while(!gridEntry.empty()){
            auto ele = gridEntry.top();
            gridEntry.pop();
            while(!pq.empty() && grid[ele.second.first][ele.second.second] >= pq.top().first){
                result[pq.top().second] = res;
                pq.pop();
            }
            res++;
            int dx[4] = {-1,0,0,1};
            int dy[4] = {0,1,-1,0};
            for(int i = 0;i < 4;i++){
                int x = ele.second.first + dx[i];
                int y = ele.second.second + dy[i];
                if(x >= 0 && x < n && y >= 0 && y < m && !visited[x][y] && grid[x][y] < cutoff){
                    visited[x][y] = true;
                    gridEntry.push({grid[x][y],{x,y}});
                }
            }
        }

        while (!pq.empty()) {
            result[pq.top().second] = res;
            pq.pop();
        }
        
        result[ind] = res;
        return result;
    }
};