class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> sq_count(n,vector<int>(m,0));
        int sum =0;
        for(int i =0;i<n;i++) {sq_count[i][0] = matrix[i][0]; sum+= sq_count[i][0];}
        for(int j =1;j<m;j++) {sq_count[0][j] = matrix[0][j]; sum+=sq_count[0][j];}
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(matrix[i][j])
                    sq_count[i][j] = min(min(sq_count[i-1][j-1],sq_count[i-1][j]),sq_count[i][j-1])+1;
                else 
                    sq_count[i][j] = 0;
                sum+=sq_count[i][j];
            }
        }

        return sum;
    }
};