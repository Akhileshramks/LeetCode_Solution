class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        int n =nums.size();
        for(int i=0;i<(1<<n);i++){
            vector<int> t;
            for(int j=0;j<n;j++){
                if(i&(1<<j)){
                    t.push_back(nums[j]);
                }
            }
            res.push_back(t);
        }
        return res;
        
    }
};