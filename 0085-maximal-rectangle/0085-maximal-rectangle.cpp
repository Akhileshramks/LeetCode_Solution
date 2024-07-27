class Solution {
public:
    int maxRect(vector<int> &nums){
        int n = nums.size();
        stack<int> st;
        st.push(0);
        int maxi = INT_MIN;
        for(int i=1;i<n;i++){
            while(!st.empty() && nums[st.top()]>nums[i]){
                int popped = st.top();
                st.pop();
                int prev_min = !st.empty() ? st.top() : -1;
                int next_min = i;
                int area = nums[popped]*(next_min-prev_min-1);
                maxi = max(maxi,area);
            }
            st.push(i);
        }
        while(!st.empty()){
            int popped = st.top();
            st.pop();
            int prev_max = !st.empty() ? st.top() : -1;
            int next_max = n;
            int area = nums[popped]*(next_max-prev_max-1);
            maxi = max(maxi,area);
        }
        return maxi;
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
            maxi = max(maxi,maxRect(num[i]));
        }
        return maxi;
    }
};