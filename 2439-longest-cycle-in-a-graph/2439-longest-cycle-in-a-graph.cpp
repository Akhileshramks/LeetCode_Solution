class Solution {
public:
    int ans = -1;
    void dfs(int src,vector<int>& edges,vector<int>& visited,vector<int>& dist,int curr){
        visited[src] = 1;
        dist[src] = curr + 1;
        if(edges[src] != -1){
            if(visited[edges[src]] == -1) dfs(edges[src],edges,visited,dist,curr+1);
            else if(visited[edges[src]] == 1){
                ans = max(ans,dist[src] - dist[edges[src]] + 1);
            }
        }
        visited[src] = 0;
    }
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<int> visited(n,-1);
        vector<int> dist(n,0);
        int curr = 0;
        for(int i = 0;i < n;i++){
            if(visited[i] == -1) dfs(i,edges,visited,dist,curr);
        }
        return ans;
    }
};
