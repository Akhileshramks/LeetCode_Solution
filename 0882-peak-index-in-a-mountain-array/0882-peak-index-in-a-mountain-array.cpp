class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int n = arr.size();
        int low = 0;
        int high = n-1;
        while(low<high){
            int mid = low+(high-low)/2;
            if(mid>0 && mid<high && arr[mid]>arr[mid+1] && arr[mid]>arr[mid-1]){
                return mid;
            }
            else if(mid<high && arr[mid]<arr[mid+1]){
                low = mid+1;
            }
            else if(mid<high && arr[mid]>arr[mid+1]){
                high = mid-1;
            }
        }
        return low;
    }
};