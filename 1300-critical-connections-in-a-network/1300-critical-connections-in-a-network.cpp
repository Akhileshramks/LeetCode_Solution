class Solution {
private:
    int time = 0;
    vector<vector<int>> res;
    void dfs(int node,int parent,vector<int> &tin,vector<int> &low,vector<vector<int>> &adj,vector<int>& visited){
        visited[node] = 1;
        tin[node] = low[node] = time;
        time++;
        for(int &neighbour : adj[node]){
            if(parent == neighbour) continue;
            if(visited[neighbour] == 0){
                dfs(neighbour,node,tin,low,adj,visited);
                low[node] = min(low[node],low[neighbour]);
                if(tin[node] < low[neighbour]){
                    res.push_back({node,neighbour});
                }
            }
            else{
                low[node] = min(low[node],low[neighbour]);
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for(auto &i : connections){
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
        }
        vector<int> tin(n);
        vector<int> low(n);
        vector<int> visited(n,0);
        for(int i = 0;i < n;i++){
            if(!visited[i]){
                dfs(i,-1,tin,low,adj,visited);
            }
        }
        return res;
    }
};