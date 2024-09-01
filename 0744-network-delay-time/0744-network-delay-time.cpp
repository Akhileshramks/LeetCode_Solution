class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        vector<vector<pair<int,int>>> adj(n);
        for(auto i : times){
            adj[i[0]-1].push_back({i[1]-1,i[2]});
        }
        pq.push({0,k-1});

        vector<int> distance(n,INT_MAX);
        distance[k-1] = 0;
        while(!pq.empty()){
            auto p = pq.top();
            pq.pop();
            for(auto [neighbour,weight] : adj[p.second]){
                if(distance[neighbour] > p.first + weight){
                    distance[neighbour]  = p.first + weight;
                    pq.push({distance[neighbour],neighbour});
                }
            }
        }
        int maxi = 0;
        for(int i =0 ;i<n;i++){
            if(distance[i] == INT_MAX) return -1;
            maxi = max(maxi,distance[i]);
        }
        return maxi;

    }
};