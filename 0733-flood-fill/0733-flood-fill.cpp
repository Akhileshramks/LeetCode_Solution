class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        queue<pair<int,int>> q;
        int n = image.size();
        int m = image[0].size();

        int check = image[sr][sc];
        if(check == color) return image;
        q.push({sr,sc});
        image[sr][sc] = color;
       
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            vector<pair<int,int>> coordinates = {{0,1},{1,0},{0,-1},{-1,0}};
            for(auto i : coordinates){
                int xx = i.first + p.first;
                int yy = i.second + p.second;
                if(xx>=0 && xx<n && yy>=0 && yy<m && image[xx][yy] == check){
                    q.push({xx,yy});
                    image[xx][yy] = color;
                }
            }
        }

        return image;
    }
};