class Solution {
public:
    bool isBipartite(vector<vector<int>>& adj,int src,int col,vector<int>& color,vector<vector<int>>& connectedComponents){
        if(color[src] != -1) return color[src] == col;
        color[src] = col;
        connectedComponents.back().push_back(src);
        for(int neighbour : adj[src]){
            if(!isBipartite(adj,neighbour,1-col,color,connectedComponents)) return false;
        }
        return true;
    }
    int bfs(vector<vector<int>>& adj,int n,vector<int> multisrc){
        int ans = 0;
        for(auto src : multisrc){
            vector<bool> visited(n,false);
            queue<int> q;
            visited[src] = true;
            q.push(src);
            int dist = 0;
            while(!q.empty()){
                int n = q.size();
                while(n--){
                    int node = q.front();
                    q.pop();
                    for(int neighbour : adj[node]){
                        if(!visited[neighbour]){
                            visited[neighbour] = true;
                            q.push(neighbour);
                        }
                    }
                }
                dist++;
                ans = max(ans,dist);
            }
        }
        return ans;
    }
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for(auto edge : edges){
            int a = edge[0];
            int b = edge[1];
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }
        int ans = 0;
        vector<int> color(n,-1);
        vector<vector<int>> connectedComponents;
        for(int i = 0;i < n;i++){
            if(color[i] == -1) {
                connectedComponents.push_back({});
                if(!isBipartite(adj,i,0,color,connectedComponents)) return -1;
            }
        }
        for(auto multisrc : connectedComponents){
            ans += bfs(adj,n,multisrc);
        }
        return ans;
    }
};