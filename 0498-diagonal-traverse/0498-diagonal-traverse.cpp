class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat){
        int m = mat.size();
        int n = mat[0].size();
        int i = 0,j = 0;
        bool upward = true;
        vector<int> ans;
        while(i < m && j < n){
            ans.push_back(mat[i][j]);
            if(i == m - 1 && j == n - 1) break;
            if(upward) i--,j++;
            else i++,j--;
            if(i == -1 || j == -1 || i == m || j == n){
                if(upward) i++,j--;
                else i--,j++;
                if(i == 0 && j == n - 1) i++;
                else if((i == m-1 && j == 0)) j++;
                else if(i == 0 || i == m - 1)j++;
                else i++;
                upward = !upward;
            }
            
        }
        return ans;
    }
};