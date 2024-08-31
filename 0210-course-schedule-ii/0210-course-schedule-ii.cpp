class Solution {
public:
    vector<int> findOrder(int n, vector<vector<int>>& prerequisites) {
        queue<int> q;

        vector<vector<int>> adj(n);
        vector<int> indegree(n,0);
        for(auto& i : prerequisites){
            adj[i[1]].push_back(i[0]);
            indegree[i[0]]++;
        }

        for(int i= 0;i<n;i++){
            if(indegree[i] == 0){
                q.push(i);
                indegree[i]--;
            }
        }
        vector<int> ans;
        while(!q.empty()){
            int p = q.front();
            q.pop();
            ans.push_back(p);
            for(auto &i : adj[p]){
                indegree[i]--;
                if(indegree[i] == 0){
                    q.push(i);
                    indegree[i]--;
                }
            }
        }
        if(ans.size() == n) return ans;
        return {};
    }
};