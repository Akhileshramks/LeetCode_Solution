class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> adj(n);
        for(int i =0;i<n;i++){
            for(auto &j : graph[i]){
                adj[j].push_back(i);
            }
        }
        graph = adj;
        vector<int> indegree(n,0);

        for(int i =0;i<n;i++){
            for(auto &j : graph[i]){
                indegree[j]++;
            }
        }

        queue<int> q;
        for(int i =0;i<n;i++){
            if(indegree[i] == 0){
                q.push(i);
                indegree[i] --;
            }
        }
        vector<int> ans;
        while(!q.empty()){
            int p = q.front();
            ans.push_back(p);
            q.pop();
            for(int &i : graph[p]){
                indegree[i]--;
                if(indegree[i] == 0){
                    q.push(i);
                    indegree[i]--;
                }
            }
        }
        sort(ans.begin(),ans.end());
        return ans;
    }
};