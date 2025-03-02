class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        int i = 0,j = 0;
        int n = nums1.size(),m = nums2.size();
        vector<vector<int>> res;
        int ind,val;
        while(i < n && j < m){
            if(nums1[i][0] == nums2[j][0]){
                ind = nums1[i][0];
                val = nums1[i][1] + nums2[j][1];
                i++;
                j++;
            }
            else if(nums1[i][0] < nums2[j][0]){
                ind = nums1[i][0];
                val = nums1[i][1];
                i++;
            }
            else{
                ind = nums2[j][0];
                val = nums2[j][1];
                j++;
            }
            res.push_back({ind,val});
        }
        while(i < n){
            ind = nums1[i][0];
            val = nums1[i][1];
            i++;
            res.push_back({ind,val});
        }
        while(j < m){
            ind = nums2[j][0];
            val = nums2[j][1];
            j++;
            res.push_back({ind,val});
        }
        return res;
    }
};