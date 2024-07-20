class Solution {
public:
    int trianglesum(int ind,int row,vector<vector<int>>& triangle){
        if(row == 0) return triangle[0][0];
        int top_left = ind>0 ? trianglesum(ind-1,row-1,triangle) : INT_MAX;
        int top_right = ind<row ? trianglesum(ind,row-1,triangle) : INT_MAX;
        return min(top_left,top_right)+triangle[row][ind];
    }
    int minimumTotal(vector<vector<int>>& triangle) {
        int rows = triangle.size();
        vector<int> prev(rows,0);
        vector<int> curr(rows,0);
        for(int row=0;row<rows;row++){
            for(int ind=0;ind<row+1;ind++){
                if(row == 0) {
                    curr[0] = triangle[0][0];
                    continue;
                }
                int top_left = ind>0 ? prev[ind-1] : INT_MAX;
                int top_right = ind<row ? prev[ind] : INT_MAX;
                curr[ind] = min(top_left,top_right)+triangle[row][ind];
            }
            prev = curr;
        }
        return *min_element(prev.begin(),prev.end());
    }
};