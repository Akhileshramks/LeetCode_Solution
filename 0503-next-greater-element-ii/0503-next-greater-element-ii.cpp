class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& arr) {
        vector<int> nums(arr.begin(),arr.end());
        nums.insert(nums.end(),arr.begin(),arr.end());
        stack<int> st;
        int n = nums.size();
        vector<int> res(n,-1);
        for(int i=0;i<n;i++){
            while(!st.empty() && nums[st.top()] < nums[i]){
                res[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }
        vector<int> result;
        for(int i = 0;i<n/2;i++) result.push_back(res[i]);
        return result;
    }
};