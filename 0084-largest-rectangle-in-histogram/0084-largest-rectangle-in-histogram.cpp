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
};