class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        priority_queue<pair<int,int>,vector<pair<int,int>>> pq;
        int n = nums.size();
        for(int i = 0;i < n;i++) pq.push({nums[i], i});
        unordered_map<int,int> mpp;
        while(k > 0){
            mpp[pq.top().second] = pq.top().first;
            pq.pop();
            k--;
        }
        vector<int> res;
        for(int i = 0;i < n;i++){
            if(mpp.find(i) != mpp.end()) res.push_back(mpp[i]);
        }
        return res;
    }
};