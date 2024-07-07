class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int maxi = 0;
        stack<int> st;
        int top;
        int width;
        for(int i=0;i<=n;i++){
            int current_height = i==n ? 0 : heights[i];
            while(!st.empty() && heights[st.top()]>current_height){
                top = st.top(); 
                st.pop();
                width = st.empty() ? i : (i-st.top()-1);
                maxi = max(maxi,heights[top]*width);
            }
            st.push(i);
        }
        return maxi;
    }
};