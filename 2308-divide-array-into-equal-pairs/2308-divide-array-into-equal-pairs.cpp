class Solution {
public:
    bool divideArray(vector<int>& nums) {
        unordered_set<int> st;
        for(int i = 0;i < nums.size();i++){
            if(st.find(nums[i]) == st.end()) st.insert(nums[i]);
            else st.erase(nums[i]);
        }
        return st.size() == 0;
    }
};