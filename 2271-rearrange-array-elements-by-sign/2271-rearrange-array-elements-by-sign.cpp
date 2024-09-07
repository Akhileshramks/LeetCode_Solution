class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> pos,neg;
        for(int i : nums){
            if(i>0) pos.push_back(i);
            else neg.push_back(i);
        }
        int n = nums.size();
        vector<int> res(nums.size());
        for(int i = 0;i<n/2;i++){
            res[2*i] = pos[i];
            res[2*i+1] = neg[i];
        }
        return res;
    }
};