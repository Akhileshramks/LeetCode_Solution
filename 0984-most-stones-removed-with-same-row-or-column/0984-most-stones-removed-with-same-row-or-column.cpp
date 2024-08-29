class Solution {
public:
    void dfs(vector<vector<int>>& adj,int ind,vector<bool> &visited){
        visited[ind] = true;
        for(int i : adj[ind]){
            if(!visited[i]){
                dfs(adj,i,visited);
            }
        }
    }
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<vector<int>> adj(n);

        for(int i = 0;i<n;i++){
            for(int j = i+1;j<n;j++){
                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        vector<bool> visited(n,false);

        int count = 0;

        for(int i=0;i<n;i++){
            if(!visited[i]){
                dfs(adj,i,visited);
                count++;
            }
        }

        return n - count;
    }
};