class Solution {
public:
    bool canFinish(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(n);
        vector<int> indegree(n,0);
        for(auto& i : prerequisites){
            adj[i[0]].push_back(i[1]);
            indegree[i[1]]++;
        }
        int c = 0;
        queue<int> q;
        for(int i =0;i<n;i++){
            if(indegree[i] == 0){
                q.push(i);
                indegree[i]--;
            }
        }
        
        while(!q.empty()){
            int p = q.front();
            c++;
            q.pop();
            for(auto & i : adj[p]){
                indegree[i]--;
                if(indegree[i] == 0){
                    q.push(i);
                }
            }
        }
        return c == n;
    }
};