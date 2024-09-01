class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> adj(n,vector<int>(n,INT_MAX));
        for(auto i : edges){
            adj[i[0]][i[1]] = i[2];
            adj[i[1]][i[0]] = i[2];
        }

        for(int k = 0;k<n;k++){
            for(int i = 0;i<n;i++){
                for(int j =0;j<n;j++){
                    if(adj[i][k]!=INT_MAX && adj[k][j]!=INT_MAX)
                    adj[i][j] = min(adj[i][j],adj[i][k]+adj[k][j]);
                }
            }
        }
        int maxi = INT_MAX;
        int res;
        for(int i = n-1;i>=0;i--){
            int count = 0;
            for(int j=0;j<n;j++){
                if(i!=j && adj[i][j] <=distanceThreshold){
                    count++;
                }
            }
            if(count<maxi){
                maxi = count;
                res = i;
            }
        }
        return res;
    }
};