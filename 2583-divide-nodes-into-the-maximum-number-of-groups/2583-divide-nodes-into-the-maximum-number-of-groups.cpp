// class Solution {
// public:
//     bool isBipartite(vector<vector<int>>& adj,int src,int col,vector<int>& color){
//         if(color[src] != -1) return color[src] == col;
//         color[src] = col;
//         for(int neighbour : adj[src]){
//             if(!isBipartite(adj,neighbour,1-col,color)) return false;
//         }
//         return true;
//     }
//     int connectedComponents(vector<vector<int>>& adj,int src,vector<bool>& visited,int n){
//         int res = bfs(adj,src,visited);
//         for(int i = 0;i < n;i++){
//             if(visited[i] && i != src){
//                 vector<bool> visited_temp(n,false);
//                 res = max(res,bfs(adj,i,visited));
//             }
//         }
//         return res;
//     }
//     int bfs(vector<vector<int>>& adj,int src,vector<bool>& visited){
//         queue<int> q;
//         visited[src] = true;
//         q.push(src);
//         int dist = 1;
//         while(!q.empty()){
//             int n = q.size();
//             while(n--){
//                 int node = q.front();
//                 q.pop();
//                 for(int neighbour : adj[node]){
//                     if(!visited[neighbour]){
//                         visited[neighbour] = true;
//                         q.push(neighbour);
//                     }
//                 }
//             }
//             dist++;
//         }
//         return dist;
//     }
//     int magnificentSets(int n, vector<vector<int>>& edges) {
//         vector<vector<int>> adj(n);
//         for(auto edge : edges){
//             int a = edge[0];
//             int b = edge[1];
//             adj[a-1].push_back(b-1);
//             adj[b-1].push_back(a-1);
//         }
//         int ans = 0;
//         vector<int> color(n,-1);
//         for(int i = 0;i < n;i++) if(color[i] == -1 && !isBipartite(adj,i,0,color) ) return -1;
//         vector<bool> visited(n,false);
//         for(int i = 0;i < n;i++){
//             if(!visited[i]){
//                 ans += connectedComponents(adj,i,visited,n);
//             }
//         }
//         return ans;
//     }
// };


class Solution {
    vector<int> color; // Tracks bipartition colors (0/1)
    vector<vector<int>> adj; // Adjacency list
    int n; // Number of nodes

    // DFS to check bipartiteness and collect component nodes
    bool isBipartite(int node, int c, vector<int>& component) {
        color[node] = c;
        component.push_back(node);
        for (int nbr : adj[node]) {
            if (color[nbr] == c) return false; // Odd cycle detected
            if (color[nbr] == -1 && !isBipartite(nbr, 1 - c, component)) 
                return false;
        }
        return true;
    }

    // BFS to compute max depth (groups) for a component
    int maxGroupsInComponent(const vector<int>& component) {
        int maxDepth = 0;
        for (int start : component) {
            vector<int> depth(n, -1);
            queue<int> q;
            q.push(start);
            depth[start] = 0;
            while (!q.empty()) {
                int node = q.front(); q.pop();
                for (int nbr : adj[node]) {
                    if (depth[nbr] == -1) {
                        depth[nbr] = depth[node] + 1;
                        maxDepth = max(maxDepth, depth[nbr]);
                        q.push(nbr);
                    }
                }
            }
        }
        return maxDepth + 1; // Depth to groups conversion
    }

public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        this->n = n;
        color.assign(n, -1);
        adj.resize(n);
        for (auto& e : edges) {
            int u = e[0] - 1, v = e[1] - 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<vector<int>> components;
        for (int i = 0; i < n; ++i) {
            if (color[i] == -1) {
                components.emplace_back();
                if (!isBipartite(i, 0, components.back())) 
                    return -1; // Non-bipartite component
            }
        }

        int total = 0;
        for (auto& comp : components) 
            total += maxGroupsInComponent(comp);
        
        return total;
    }
};