class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end());
        int end = intervals[0][1];
        int start = intervals[0][0];
        vector<vector<int>> res;
        int n = intervals.size();
        for(int i =1;i<n;i++){
            if(intervals[i][0]<end){
                end = min(end,intervals[i][1]);
            }
            else{
                res.push_back({start,end});
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }
        res.push_back({start,end});
        return n-res.size();
    }
};