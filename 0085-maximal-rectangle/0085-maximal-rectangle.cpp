class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> st;
        int res = 0;
        for(int i = 0; i <= n; i++){
            int currentHeight = i == n ? 0 : heights[i];
            while(!st.empty() && currentHeight < heights[st.top()]){
                int eleInd = st.top();
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                res = max(res,width * heights[eleInd]);
            }
            st.push(i);
        }
        return res;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> num(n,vector<int>(m,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i==0){
                    num[i][j] = matrix[i][j]=='1' ? 1 : 0;
                }
                else{
                    num[i][j] = matrix[i][j]=='1' ? 1+num[i-1][j] : 0;
                }
            }
        }
        int maxi = 0;
        for(int i=0;i<n;i++){
            maxi = max(maxi,largestRectangleArea(num[i]));
        }
        return maxi;
    }
};