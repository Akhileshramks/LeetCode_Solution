class Solution {
public:
    bool isPossible(vector<int>& start, long long diff, long long d){
        int s = start[0];
        for(int i =1 ;i< start.size();i++){
            if(s + diff > start[i]+d) return false;
            else{
                s = s + diff < start[i] ? start[i] :  s + diff;
            }
        }
        return true;
    }
    int maxPossibleScore(vector<int>& start, int d) {
        sort(start.begin(),start.end());
        int n = start.size();
        long long low = 0;
        long long high = start[n-1] - start[low] + d;
        while(low <= high){
            long long mid = low + (high-low)/2;
            if(isPossible(start,mid,d)){
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }
        return high;
    }
};