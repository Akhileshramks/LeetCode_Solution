class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        stack<int> st;
        vector<int> NSE(n,n),PSEE(n,-1),NGE(n,n),PGEE(n,-1);
        for(int i=0;i<n;i++){
            while(!st.empty() && nums[st.top()] < nums[i]){
                NGE[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>();
        for(int i=0;i<n;i++){
            while(!st.empty() && nums[st.top()] > nums[i]){
                NSE[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>();
        for(int i=0;i<n;i++){
            while(!st.empty() && nums[st.top()] > nums[i]) st.pop();
            if(!st.empty()) PSEE[i] = st.top();
            st.push(i);
        }
        st = stack<int>();
        for(int i=0;i<n;i++){
            while(!st.empty() && nums[st.top()] < nums[i]) st.pop();
            if(!st.empty()) PGEE[i] = st.top();
            st.push(i);
        }
        long long sum = 0;
        for(int i =0;i<n;i++){
            int left_S = i - PSEE[i];
            int right_S = NSE[i] - i;
            int left_G = i - PGEE[i];
            int right_G = NGE[i] - i;
            sum += (left_G*right_G - left_S*right_S*1ll)*nums[i];
        }
        return sum;
    }
};