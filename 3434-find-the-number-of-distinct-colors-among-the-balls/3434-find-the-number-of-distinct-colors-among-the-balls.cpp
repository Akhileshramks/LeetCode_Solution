class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int,unordered_set<int>> color;
        unordered_map<int,int> assigned;
        vector<int> res;
        for(auto i : queries){
            int last = -1;
            int node = i[0];
            int col = i[1];
            if(assigned.find(node) != assigned.end()) last = assigned[node];
            if(last != -1){
                if(color[last].size() == 1) color.erase(last);
                else color[last].erase(node);
            }
            assigned[node] = col;
            color[col].insert(node);
            res.push_back(color.size());
        }
        return res;
    }
};