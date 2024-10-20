class Solution {
public:
    static bool comp(const vector<int>&a,const vector<int> &b){
        return a[1]<b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),comp);
        int end = intervals[0][1],n = intervals.size(),count =1;
        for(int i =1;i<n;i++){
            if(intervals[i][0]>=end){
                count++;
                end = intervals[i][1];
            }
        }
        return n-count;
    }
};