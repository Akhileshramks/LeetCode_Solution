class Solution {
public:
    bool bipartite(vector<vector<int>>& graph,int src,int color,vector<int> &visited){
        visited[src] = color;
        for(int i : graph[src]){
            if(visited[i] == -1){
                if(!bipartite(graph,i,1-color,visited)) return false;
            }
            else if(visited[i] == color){
                return false;
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> visited(n,-1);
        bool flag = true;
        for(int i =0;i<n;i++){
            if(visited[i] == -1)
                if(!bipartite(graph,i,1,visited)) return false;
        }
        return flag;
    }
};