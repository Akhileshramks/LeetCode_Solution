class Solution {
public:
    void dfs(vector<vector<int>>& isConnected,int src,vector<bool> &visited){
        visited[src] = true;
        for(int des = 0; des<isConnected.size(); des++){
            if(!visited[des] && isConnected[src][des]){
                dfs(isConnected,des,visited);
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n,false);

        int provinces = 0;

        for(int src = 0;src<n;src++){
            if(!visited[src]){
                dfs(isConnected,src,visited);
                provinces++;
            }
        }
        return provinces;
    }
};