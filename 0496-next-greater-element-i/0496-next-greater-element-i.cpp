class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums2.size();
        unordered_map<int,int> NGE;
        vector<int> res;
        stack<int> st;
        for(int i =0;i<n;i++){
            while(!st.empty() && st.top() < nums2[i]){
                NGE[st.top()] = nums2[i];
                st.pop();
            }
            st.push(nums2[i]);
        }
        for(int &i : nums1){
            int m = NGE[i] == 0 ? -1 : NGE[i];
            res.push_back(m);
        }
        return res;
    }
};