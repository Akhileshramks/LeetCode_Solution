class Solution {
public:
    int dijkstra(vector<vector<int>>& edges,int src,int des,int n){
        vector<vector<pair<int,int>>> adj(n);
        for(auto &i : edges){
            if(i[2] != -1){
                adj[i[0]].push_back({i[1],i[2]});
                adj[i[1]].push_back({i[0],i[2]});
            }
        }

        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

        pq.push({0,src});
        vector<int> distance(n,INT_MAX);
        distance[src] = 0;
        while(!pq.empty()){
            auto p = pq.top();
            int d = p.first;
            int s = p.second;
            pq.pop();
            if(distance[s] < d) continue;
            for(auto &[dest,w] : adj[s]){
                if( (w+d) < distance[dest]){
                    distance[dest] = w + d;
                    pq.push({distance[dest],dest});
                }
            }
        }
        return distance[des];
    }
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
    
        int shortest = dijkstra(edges,source,destination,n);
        if(shortest < target) return {};
        bool flag = shortest == target;
        for(auto &e : edges){
            if(e[2] != -1) continue;
            e[2] = flag ? 2e9 : 1;
            if(!flag){
                int shortest_new = dijkstra(edges,source,destination,n);
                if(shortest_new <= target){
                    flag = true;
                    e[2] += target-shortest_new;
                }
            }
        }
        return flag ? edges : vector<vector<int>>();
    }
};