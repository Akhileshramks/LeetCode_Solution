class Solution {
public:
    vector<char> changeColumnWise(vector<char> row){
        int n = row.size();
        vector<int> ans(n , 0);
        int count = 0;
        for(int i = 0;i < n;i++){
            if(row[i] == '#') count++;
            if(row[i] == '*' || i == n - 1){
                ans[i] = count;
                count = 0;
            }
        }
        count = ans[n-1];
        for(int i = n - 1;i >= 0;i--){
            if(row[i] == '*') count = ans[i];
            else if(count > 0){
                row[i] = '#';
                count--;
            }
            else row[i] = '.';
        }
        return row;
    }
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int n = boxGrid.size();
        int m = boxGrid[0].size();
        vector<vector<char>> result(m, vector<char>(n, '.'));
        for(int i = 0;i < n;i++){
            vector<char> res = changeColumnWise(boxGrid[i]);
            for(int j = 0;j < m;j++){
                result[j][n - i - 1] = res[j];
            }
        }
        return result;
    }
};