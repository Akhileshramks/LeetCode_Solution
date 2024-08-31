class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {

        int n = heights.size(); //no of rows
        int m = heights[0].size(); // no of cols
        //Queue - { {distance,{x,y}} }
        priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> q;

        vector<vector<int>> distance(n,vector<int>(m,INT_MAX));
        distance[0][0] = 0;
        q.push({0,{0,0}});
        int maxi =0;
        vector<pair<int,int>> coordinates = {{0,1},{1,0},{0,-1},{-1,0}};
        while(!q.empty()){
            auto p = q.top();
            q.pop();
            int d = p.first;
            int x = p.second.first;
            int y = p.second.second;
            if(x == n-1 && y == m-1) continue;
            for(auto [dx,dy] : coordinates){
                int xx = x+dx;
                int yy = y+dy;
                if(xx>=0 && xx<n && yy>=0 && yy<m){
                    int new_effort = max(d,abs(heights[x][y] - heights[xx][yy]));
                    if(distance[xx][yy] > new_effort){
                        distance[xx][yy] = new_effort;
                        q.push({distance[xx][yy],{xx,yy}});
                    }
                }
            }
        }
        return distance[n-1][m-1];
    }
};