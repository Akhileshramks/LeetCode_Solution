class Solution {
public:
    int minpathsum(int m,int n,vector<vector<int>>& matrix){
        if(m == 0){
            int mini = INT_MAX;
            for(int i= -1;i<2;i++){
                if(n>0 && n+i<matrix[0].size())
                    mini = min(mini,matrix[0][n+i]);
            }
            return mini;
        }
        else{
            int mini = INT_MAX;
            for(int i= -1;i<2;i++){
                if(n>0 && n+i<matrix[0].size())
                    mini = min(mini,minpathsum(m-1,n+i,matrix));
            }
            return mini+matrix[m][n];
        }
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols =matrix[0].size();
        int mini = INT_MAX;
        vector<int> prev(cols,0);
        vector<int> curr(cols,0);
        for(int i=0;i<cols;i++){
            prev[i] = matrix[0][i];
        }
        for(int row = 1;row<rows;row++){
            for(int col = 0;col<cols;col++){
                int mini = INT_MAX;
                for(int i=-1;i<2;i++){
                    if(col+i>=0 && col+i<cols)
                        mini = min(mini,prev[col+i]);
                }
                curr[col] = mini+matrix[row][col];
            }
            prev = curr;
        }
        return *min_element(prev.begin(),prev.end());
    }
};