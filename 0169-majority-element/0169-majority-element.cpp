class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int major = nums[0];
        int n = nums.size();
        int count = 0;
        for(int i = 0;i < n;i++){
            if(count == 0) major = nums[i];
            if(major == nums[i]) count++;
            else count--;
        }
        return major;
    }
};