class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        int n = temperatures.size();
        vector<int> res(n,0);
        for(int i =0;i<n;i++){
            while(!st.empty() && temperatures[st.top()]<temperatures[i]){
                int p = st.top();
                st.pop();
                res[p] = i-p;
            }
            st.push(i);
        }
        return res;
    }
};