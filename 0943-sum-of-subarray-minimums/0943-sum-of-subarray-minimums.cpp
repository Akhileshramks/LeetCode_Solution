class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        stack<int> st;
        int n = arr.size();
        vector<int> PSE(n,-1),NSE(n,n);
        for(int i =0;i<n;i++){
            while(!st.empty() && arr[st.top()] > arr[i]){
                NSE[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>();
        for(int i =0;i<n;i++){
            while(!st.empty() && arr[st.top()] > arr[i]) st.pop();
            if(!st.empty()) PSE[i] = st.top();
            st.push(i);
        }
        int sum = 0 ;
        for(int i=0;i<n;i++){
            int left = i - PSE[i];
            int right = NSE[i] - i;
            sum = (sum + (left*right*1LL*arr[i]%MOD)%MOD)%MOD;
        }
        return sum;
    }
};

/*

[   3      1      2      4  ]
    -1      2
    -1      3
*/