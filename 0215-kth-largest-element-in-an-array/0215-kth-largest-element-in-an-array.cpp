class Solution {
public:
    void heapify(vector<int>& nums,int ind,int n){
        int left = 2*ind+1;
        int right = 2*ind+2;
        int largest = ind;
        if (left<n && nums[left]>nums[largest]){
            largest = left;
        }
        if(right<n && nums[right]>nums[largest]){
            largest = right;
        }
        if(largest!=ind){
            swap(nums[largest],nums[ind]);
            heapify(nums,largest,n);
        } ;
    }
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        for(int i=n/2-1;i>=0;i--) heapify(nums,i,n);
        for(int i =n-1;i>n-k;i--){
            swap(nums[0],nums[i]);
            heapify(nums,0,i);
        }
        return nums[0];
    }
};