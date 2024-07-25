class Solution {
public:
    void merge(int l,int m,int h,vector<int>& nums){
        int n1 = m-l+1;
        int n2 = h-m;
    }
    void mergesort(int l,int h,vector<int>& nums){
        if(l<h){
            int mid = l+(h-l)/2;
            mergesort(l,mid,nums);
            mergesort(mid+1,h,nums);
            merge(l,mid,h,nums);
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        return nums;
    }
};