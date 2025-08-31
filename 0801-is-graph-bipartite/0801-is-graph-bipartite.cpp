class Solution {
public:
    bool dfs(vector<vector<int>>& graph, vector<int>& colorAssigned,int color,int src){
        colorAssigned[src] = color;
        for(int neighbour : graph[src]){
            if(colorAssigned[neighbour] == -1){
                if(dfs(graph,colorAssigned,1 - color, neighbour) == false) return false;
            }else if(1 - color != colorAssigned[neighbour]) return false;
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> colorAssigned(n, -1);
        for(int i = 0;i < n;i++){
            if(colorAssigned[i] == -1){
                if(dfs(graph,colorAssigned,1,i) == false) return false;
            }
        }
        return true;
    }
};