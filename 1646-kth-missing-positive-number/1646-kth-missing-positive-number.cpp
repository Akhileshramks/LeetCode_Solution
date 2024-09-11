class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int n = arr.size();
        int low = 0;
        int high = n-1;
        while(low<=high){
            int mid = low + (high-low)/2;
            int number_missing = arr[mid] - mid -1;
            if(number_missing < k){
                low = mid + 1;
            }
            else{
                high = mid-1;
            }
        }
        return k+high+1;
    }
};
/*
2 3 4 7 11
0 1 2 3 4
1 1 1 3 6

*/