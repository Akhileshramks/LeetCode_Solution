class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        nums.push_back(k);
        int n = nums.size();
        sort(nums.begin(),nums.end(),greater<>());
        int last = -1;
        int count = 0;
        for(int i = 0;i < n;i++){
            if(nums[i] == k) break;
            if(last == -1 || last != nums[i]){
                last = nums[i];
                count++;
            }
        }
        if(nums[n-1] == k) return count;
        return -1;
    }
};