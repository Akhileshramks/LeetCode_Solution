class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        stack<pair<int, pair<int,int>>> st;
        for(int i = 0;i < n;i++){
            pair<int, pair<int,int>> newElem = {nums[i], {i, i}};
            while(!st.empty() && st.top().first > nums[i]){
                auto k = st.top();
                st.pop();
                newElem.first = max(newElem.first, k.first);
                newElem.second.first = k.second.first;
            }
            st.push(newElem);
        }
        while(!st.empty()){
            auto k = st.top();
            st.pop();
            for(int j = k.second.first;j <= k.second.second;j++) res[j] = k.first;
        }
        return res;
    }
};