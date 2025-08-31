class Solution {
public:
    void dfs(vector<vector<int>>& isConnected, vector<bool>& visited,int src,int n){
        visited[src] = true;
        for(int neighbour = 0; neighbour < n;neighbour++){
            if(isConnected[src][neighbour] == 1 && !visited[neighbour]){
                dfs(isConnected,visited,neighbour,n);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int noOfNeighbour = 0;
        int n = isConnected.size();
        vector<bool> visited(n, false);
        for(int i = 0;i < n;i++){
            if(!visited[i]){
                noOfNeighbour++;
                dfs(isConnected, visited, i, n);
            }
        }
        return noOfNeighbour;
    }
};