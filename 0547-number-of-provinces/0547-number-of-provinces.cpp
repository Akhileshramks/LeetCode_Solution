class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<vector<int>> adj(n);
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(isConnected[i][j] == 1) adj[i].push_back(j);
            }
        }
        vector<bool> visited(n, false);
        queue<int> q;
        int count = 0;
        for(int i = 0;i < n;i++){
            if(!visited[i]){
                count += 1;
                visited[i] = true;
                q.push(i);
                while(!q.empty()){
                    int front = q.front();
                    q.pop();
                    for(int m : adj[front]){
                        if(!visited[m]){
                            q.push(m);
                            visited[m] = true;
                        }
                    }
                }
            }
        }
        return count;
    }
};