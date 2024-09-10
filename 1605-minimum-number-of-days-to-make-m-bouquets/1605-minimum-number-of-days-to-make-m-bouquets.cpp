class Solution {
public:
    int checkPossible(vector<int>& bloomDay,int day,int k){
        int count = 0;
        int ans = 0;
        for(int i : bloomDay){
            if(i<=day) count++;
            else count = 0;
            if(count == k) ans++,count=0;
        }
        return ans;
    }
    int minDays(vector<int>& bloomDay, int m, int k) {
        vector<int> sortedBloomDay = bloomDay;
        sort(sortedBloomDay.begin(),sortedBloomDay.end());
        int n = sortedBloomDay.size();
        int low = 0;
        int high = sortedBloomDay.size()-1;
        while(low <= high){
            int mid = low + (high - low)/2;
            if(checkPossible(bloomDay,sortedBloomDay[mid],k) >= m){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return low == n ? -1 : sortedBloomDay[low];
    }
};