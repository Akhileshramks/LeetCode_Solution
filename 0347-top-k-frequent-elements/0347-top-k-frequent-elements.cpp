class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> mpp;
        for(auto &i : nums) mpp[i]++;
        priority_queue< pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        for(auto &[i,j] : mpp){
            pq.push({j,i});
            if(pq.size()>k) pq.pop();
        }
        vector<int> res;
        while(!pq.empty()){
            res.push_back(pq.top().second);
            pq.pop();
        } 
        reverse(res.begin(),res.end());
        return res;
    }
};