class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> s;
        int n = nums.size();
        int i = 0;
        int sum1 = 0;
        int count = 0;
        s[0] = 1;
        for(int i=0;i<n;i++){
            sum1+=nums[i];
            count+=s[sum1-k];
            s[sum1] +=1;
        }
        return count;

    }
};