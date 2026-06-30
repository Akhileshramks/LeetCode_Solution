class Solution {
public:
    vector<vector<int>> filterOccupiedIntervals(vector<vector<int>>& occupiedIntervals, int freeStart, int freeEnd) {
        vector<vector<int>> res;
        sort(occupiedIntervals.begin(), occupiedIntervals.end());
        res.push_back(occupiedIntervals[0]);
        int n = occupiedIntervals.size();
        for(int i = 1;i < n;i++){
            vector<int>& last = res.back();
            vector<int>& curr = occupiedIntervals[i];

            if(curr[0] <= last[1] + 1) last[1] = max(last[1], curr[1]);
            else res.push_back(curr);
        }

        vector<vector<int>> finalRes;
        for(auto curr : res){
            int l = curr[0];
            int r = curr[1];

            if(r < freeStart || l > freeEnd){
                finalRes.push_back(curr);
                continue;
            }

            if(l < freeStart){
                finalRes.push_back({l, freeStart - 1});
            }

            if(r > freeEnd){
                finalRes.push_back({freeEnd + 1, r});
            }
        }
        return finalRes;
    }
};