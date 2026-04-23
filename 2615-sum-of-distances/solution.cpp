class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        int MOD = 1e9 + 7;
        long long leftSum = 0, rightSum = 0;
        vector<long long> res(n,0);
        unordered_map<int,pair<long long,long long>> mpp;
        for(int i = n-1;i >= 0;i--){
            if(mpp.find(nums[i]) != mpp.end()){
                leftSum = mpp[nums[i]].first;
                rightSum = i * mpp[nums[i]].second; 
                res[i] += leftSum - rightSum;
            }
            mpp[nums[i]].first += i;
            mpp[nums[i]].second++;
        }
        mpp.clear();
        for(int i = 0;i < n;i++){
            if(mpp.find(nums[i]) != mpp.end()){
                leftSum = mpp[nums[i]].first;
                rightSum = i * mpp[nums[i]].second; 
                res[i] += rightSum - leftSum;
            }
            mpp[nums[i]].first += i;
            mpp[nums[i]].second++;
        }
        return res;
    }
};

/*

0 1 2 3 4 5 6
1 - 1 - 1 1 -


5 - 4 = 1

5 - 2 = 3 
4 - 2 = 2 

5 - 1 => 4
4 - 1 => 3 
2 - 1 => 1

*/
