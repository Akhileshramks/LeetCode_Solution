class Solution {
public:
    bool checkCompleteComponent(int n,vector<vector<int>>& adj,vector<bool>& visited,int src){
        unordered_set<int> st;
        queue<int> q;
        q.push(src);
        visited[src] = true;
        int nodeInComponent = 1;
        while(!q.empty()){
            int m = q.front();
            q.pop();
            st.insert(adj[m].size());
            for(auto neighbour : adj[m]){
                if(visited[neighbour]) continue;
                q.push(neighbour);
                visited[neighbour] = true;
                nodeInComponent++;
            }
        }
        if(st.size() == 1 && *st.begin() == nodeInComponent - 1) return true;
        return false;
    }
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        int m = edges.size();
        for(int i = 0;i < m;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        vector<bool> visited(n,false);
        int res = 0;
        for(int i = 0;i < n;i++){
            if(!visited[i] && checkCompleteComponent(n,adj,visited,i)){
                res++;
            }
        }
        return res;
    }
};