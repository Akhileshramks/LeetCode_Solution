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
        int n = bloomDay.size();
        int low = *min_element(bloomDay.begin(),bloomDay.end());
        int high = *max_element(bloomDay.begin(),bloomDay.end());
        int maxi = *max_element(bloomDay.begin(),bloomDay.end());
        while(low <= high){
            int mid = low + (high - low)/2;
            if(checkPossible(bloomDay,mid,k) >= m){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return low > maxi ? -1 : low;
    }
};