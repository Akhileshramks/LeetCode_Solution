class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {

        stack<int> st;
        int MOD = 1e9+7;
        int n = arr.size();
        vector<int> prevSmaller(n,-1);
        for(int i = 0;i < n;i++){
            while(!st.empty() && arr[st.top()] > arr[i]){
                st.pop();
            }
            if(!st.empty()) prevSmaller[i] = st.top();
            st.push(i);
        }
        vector<int> nextSmaller(n,n);
        long long res = 0;
        st = stack<int>();
        for(int i = 0;i < n ;i++){
            while(!st.empty() && arr[st.top()] > arr[i]){
                nextSmaller[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        for(int i = 0;i<n;i++){
            int left = i - prevSmaller[i];
            int right = nextSmaller[i] -i;
            res = (res + ((left*right*1LL)%MOD*arr[i]*1LL)%MOD)%MOD;
        }
        return res;
    }
};