class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(nums.size());
        int negIndex = 1;
        int posIndex = 0;
        for(int i =0;i<n;i++){
            if(nums[i]<0) res[negIndex] = nums[i],negIndex+=2;
            else res[posIndex] = nums[i],posIndex+=2;
        }
        return res;
    }
};