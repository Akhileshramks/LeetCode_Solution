class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        int n = arr.size();
        for(int i = 0; i < n; i++){
            pq.push({arr[i],i});
        }
        int rank = 0;
        int last = INT_MIN;
        vector<int> res(n,0);
        while(!pq.empty()){
            auto i = pq.top();
            pq.pop();
            if(i.first > last){
                rank++;
                last = i.first;
            }
            res[i.second] = rank;
        }
        return res;
    }
};