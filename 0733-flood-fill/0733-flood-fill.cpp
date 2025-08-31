class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        queue<pair<int,int>> q;
        int m = image.size(), n = image[0].size();
        int srcColor = image[sr][sc];
        if(srcColor == color) return image;
        image[sr][sc] = color;
        q.push({sr, sc});
        int dx[4] = {0,0,1,-1};
        int dy[4] = {-1,1,0,0};
        while(!q.empty()){
            auto top = q.front();
            int x = top.first;
            int y = top.second;
            q.pop();
            image[x][y] = color;
            for(int k = 0;k < 4;k++){
                int dxx = x + dx[k];
                int dyy = y + dy[k];
                if(dxx >= 0 && dyy >= 0 && dxx < m && dyy < n && image[dxx][dyy] == srcColor){
                    image[dxx][dyy] = color;
                    q.push({dxx,dyy});
                }
            }
        }
        return image;
    }
};