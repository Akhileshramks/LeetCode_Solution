class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0;
        int right = 0;
        int count = 0;
        int n = nums.size();
        int jump;
        int maxi = 0;
        queue<int> q;
        while(right<n){
            if(nums[right] == 0){
                q.push(right);
                count+=1;
            }
            if(count>k){
                left = q.front()+1;
                q.pop();
                count--;
            }
            maxi = max(right-left+1,maxi);
            right++;
        }
        return maxi;
    }
};