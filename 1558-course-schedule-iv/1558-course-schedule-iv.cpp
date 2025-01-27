class Solution {
public:
    bool bfs(int src,int dest,vector<vector<int>>& adj,int n){
        queue<int> q;
        vector<int> visited(n,0);
        q.push(src);
        visited[src] = 1;
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(int neighbour : adj[p]){
                if(neighbour == dest) return true;
                if(!visited[neighbour]){
                    visited[neighbour] = 1;
                    q.push(neighbour);
                }   
            }
        }
        return false;
    }
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<bool> res;
        vector<vector<int>> adj(numCourses);
        int src,dest;
        for(auto i : prerequisites){
            src = i[0];
            dest = i[1];
            adj[src].push_back(dest);
        }
        for(auto i : queries){
            src = i[0];
            dest = i[1];
            res.push_back(bfs(src,dest,adj,numCourses));
        }
        return res;
    }
};