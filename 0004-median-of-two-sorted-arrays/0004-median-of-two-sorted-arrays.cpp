class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        if(n > m) return findMedianSortedArrays(nums2,nums1);
        double median;
        int left = (n+m+1)/2;
        int low = 0;
        int high = n;
        bool flag = (n + m) % 2 == 0 ? true : false;
        while(low <= high){
            int l1 = INT_MIN;
            int l2 = INT_MIN;
            int r1 = INT_MAX;
            int r2 = INT_MAX;
            int mid1 = low + (high - low)/2;
            int mid2 = left - mid1;
            if(mid1 - 1 >= 0) l1 = nums1[mid1 - 1];
            if(mid2 - 1 >= 0) l2 = nums2[mid2 - 1];
            if(mid1 < n) r1 = nums1[mid1];
            if(mid2 < m) r2 = nums2[mid2];

            if(l1 <= r2 && l2 <= r1){
                if(flag) median = (min(r1,r2) + max(l1,l2)) / 2.0;
                else median = max(l1,l2);
                return median;
            }

            else if(l1 > r2){
                high = mid1 - 1;
            }
            else{
                low = mid1 + 1;
            }
        }
        return -1;
    }
};