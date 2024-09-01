#define ll long long
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        vector<ll> distance(n,LONG_MAX);
        vector<ll> ways(n);
        priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
        vector<vector<pair<int,int>>> adj(n);
        for(auto i : roads){
            adj[i[0]].push_back({i[1],i[2]});
            adj[i[1]].push_back({i[0],i[2]});
        }
        distance[0] = 0;
        ways[0] = 1;
        pq.push({0,0});
        int mod = (int)1e9+7;
        while(!pq.empty()){
            auto [dist , node] = pq.top();
            pq.pop();

            for(auto [adjacent,weight] : adj[node]){
                if(distance[adjacent] > weight + dist){
                    distance[adjacent] = weight + dist;
                    ways[adjacent] = ways[node];
                    pq.push({distance[adjacent],adjacent});
                }
                else if(distance[adjacent] == weight + dist){
                    ways[adjacent] = (ways[adjacent] + ways[node]) %mod;
                }
            }
        }
        //ways[n-1] %= mod;
        return ways[n-1];
    }
};