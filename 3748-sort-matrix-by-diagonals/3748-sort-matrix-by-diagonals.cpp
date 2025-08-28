class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        for(int i = 0;i < n;i++){
            vector<int> temp;
            for(int j = 0;j < n - i;j++){
                temp.push_back(grid[i+j][j]);
            }
            sort(temp.begin(), temp.end(), greater<int>());
            for(int j = 0;j < n - i;j++){
                grid[i+j][j] = temp[j];
            }
        }
        for(int i = 1;i < n;i++){
            vector<int> temp;
            for(int j = i;j < m;j++){
                temp.push_back(grid[j - i][j]);
            }
            sort(temp.begin(), temp.end());
            for(int j = i;j < m;j++){
                grid[j - i][j] = temp[j - i];
            }
        }
        return grid;
    }
};