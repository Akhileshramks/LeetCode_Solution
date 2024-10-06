class Solution {
public:
    void dfs(vector<vector<int>>& adj, int src, vector<int>& visited, vector<int>& res, int k) {
        visited[src] = 1;
        res[k] = src;
        for (int& neighbour : adj[src]) {
            if (!visited[neighbour]) {
                dfs(adj, neighbour, visited, res, k + 1);
            }
        }
    }

    void bfs(vector<vector<int>>& adj, int src, vector<int>& distance, vector<int>& parent) {
        int n = adj.size();
        distance[src] = 0;
        queue<int> q;
        q.push(src);
        while (!q.empty()) {
            int p = q.front();
            q.pop();
            for (int& neighbour : adj[p]) {
                if (distance[neighbour] > 1 + distance[p]) {
                    distance[neighbour] = 1 + distance[p];
                    parent[neighbour] = p;
                    q.push(neighbour);
                }
            }
        }
    }

    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        vector<int> indegree(n, 0);
        vector<vector<int>> adj(n);
        vector<int> visited(n, 0);

        for (auto& i : edges) {
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
            indegree[i[0]]++;
            indegree[i[1]]++;
        }
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 1) {
                vector<int> res(n, 0);
                dfs(adj, i, visited, res, 0);
                vector<vector<int>> ans;
                ans.push_back(res);
                return ans;
            }
        }

        vector<int> edgeNode;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 2) {
                edgeNode.push_back(i);
            }
        }

        if (edgeNode.size() < 4) {
            return vector<vector<int>>(); 
        }

        vector<int> distance(n, INT_MAX);
        vector<int> parent(n, -1);
        bfs(adj, edgeNode[0], distance, parent);

        int rowSize = min({distance[edgeNode[1]], distance[edgeNode[2]], distance[edgeNode[3]]}) + 1;
        cout<<"RowSize: "<<rowSize<<endl;
        int colSize = n / rowSize;
        cout<<"ColSize: "<<colSize<<endl;
        int minNode = -1;
        for (int i = 1; i < 4; i++) {
            if (distance[edgeNode[i]] == rowSize - 1) {
                minNode = edgeNode[i];
                break;
            }
        }

        vector<vector<int>> matrix(colSize, vector<int>(rowSize, 0));
        matrix[0][0] = edgeNode[0];

        for (int i = rowSize - 1; i >= 1; i--) {
            matrix[0][i] = minNode;
            minNode = parent[minNode];
        }

        for (int i = 1; i < colSize; i++) {
            for (int j = 0; j < rowSize; j++) {
                unordered_set<int> st(adj[matrix[i - 1][j]].begin(), adj[matrix[i - 1][j]].end());
                if (j > 0) st.erase(matrix[i - 1][j - 1]);
                if (i - 1 > 0) st.erase(matrix[i - 2][j]);
                if (j + 1 < rowSize) st.erase(matrix[i - 1][j + 1]);
                matrix[i][j] = *st.begin();

            }
        }

        return matrix;
    }
};
