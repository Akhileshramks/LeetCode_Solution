class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n,false);
        queue<int> q;
        int provinces = 0;
        for(int src = 0 ; src < n ; src++){
            if(!visited[src]){
                provinces++;
                q.push(src);
                visited[src] = true;
                while(!q.empty()){
                    int s = q.front();
                    q.pop();
                    for(int des = 0;des<n;des++){
                        if(isConnected[s][des] && !visited[des]){
                            q.push(des);
                            visited[des] = true;
                        }
                    }
                }
            }
        }
        return provinces;
    }

};