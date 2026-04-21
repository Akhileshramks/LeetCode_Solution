class Graph{
    public:
        vector<int> parent;
        vector<int> size;
    Graph(int n){
        parent.resize(n);
        size.resize(n,1);
        for(int i = 0;i < n;i++) parent[i] = i;
    }
    int findUltimateParent(int n){
        if(parent[n] == n) return n; 
        return parent[n] = findUltimateParent(parent[n]);
    }
    void mergeParent(int i, int j){
        int ul_i = findUltimateParent(i);
        int ul_j = findUltimateParent(j);
        if(ul_i == ul_j) return;
        if(size[ul_i] >= size[ul_j]){
            parent[ul_j] = ul_i;
            size[ul_i] += size[ul_j];
        }else{
            parent[ul_i] = ul_j;
            size[ul_j] += size[ul_i];
        }
    }
};
class Solution {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        int result = 0;
        Graph g(n);
        for(auto i : allowedSwaps){
            g.mergeParent(i[0],i[1]);
        }
        unordered_map<int,unordered_map<int,int>> mpp;
        for(int i = 0;i < n;i++){
            int ul_i = g.findUltimateParent(i);
            mpp[ul_i][source[i]]++;
        }
        for(int i = 0;i < n;i++){
            int ul_i = g.findUltimateParent(i);
            if(mpp[ul_i][target[i]] > 0) mpp[ul_i][target[i]]--;
            else result++;
        }
        return result;
    }
};