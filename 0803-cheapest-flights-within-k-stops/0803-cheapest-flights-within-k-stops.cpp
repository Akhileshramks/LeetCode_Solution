class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;

        vector<vector<vector<int>>> adj(n);

        for(auto i : flights){
            adj[i[0]].push_back({i[1],i[2]});
        }

        pq.push({0,{src,0}});
        vector<int> distance(n,INT_MAX);
        distance[src] = 0;
        while(!pq.empty()){
            auto p = pq.top();
            pq.pop();
            if(p.first > k) continue;
            for(auto i : adj[p.second.first]){
                if(distance[i[0]] > p.second.second + i[1]){
                    distance[i[0]] = p.second.second + i[1];
                    pq.push({p.first+1,{i[0],p.second.second + i[1]}});
                }
            }
        }
        return distance[dst] == INT_MAX ? -1 : distance[dst];

    }
};