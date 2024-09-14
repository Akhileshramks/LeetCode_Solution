class Solution {
public:
    static bool comp(const vector<int>&a,const vector<int> &b){
        return a[1]<b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),comp);
        int end = intervals[0][1];
        int prev = 0,n = intervals.size(),count =1;
        for(int i =1;i<n;i++){
            if(intervals[i][0]>=intervals[prev][1]){
                count++;
                prev = i;
            }
        }
        return n-count;
    }
};