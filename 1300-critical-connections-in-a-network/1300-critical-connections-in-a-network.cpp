class Solution {
public:
    int step = 0;
    void dfs(vector<vector<int>>& adj,int node, int parent, vector<int> &way, vector<int> &curr,vector<int> &visited,vector<vector<int>> &res){
        visited[node] = true;
        step++;
        curr[node] = step;
        way[node] = step;
        for(int neighbour : adj[node]){
            if(neighbour == parent) continue;
            if(!visited[neighbour]){
                
                dfs(adj,neighbour,node,way,curr,visited,res);
                way[node] = min(way[node] , way[neighbour]);
                if(curr[node] < way[neighbour]){
                    res.push_back({node,neighbour});
                }
            }
            else{
                way[node] = min(way[node] , way[neighbour]);
            }
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for(auto i : connections){
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
        }
        vector<int> curr(n,-1);
        vector<int> way(n,-1);
        vector<int> visited(n,false);
        vector<vector<int>> res;
        dfs(adj,0,-1,way,curr,visited,res);
        return res;
    }
};